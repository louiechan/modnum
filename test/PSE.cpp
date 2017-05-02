//
// Created by 陈路 on 2017/4/30.
//

#include <modnum.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class PSE{
private:
    vector<char> cipher;//密文
    vector<char> plaintext;//明文
    vector<char> decrypted_text;//解密过后的text
    vector<Matrix> key;//密钥
    int plaintext_inteval;//填充明文的位数0~2
    int start; //替换表的首元素，默认为空格
    int table_length;//替换表长度，默认为所有可显字符的长度
public:
    PSE(); //自己生成ey
    PSE( vector<Matrix> k);//调用者生成key
    ~PSE(){}
    void setTable(int start,int end);//设定替换表的范围
    void generateKey();
    bool isKeyValidate();
    void setKey(vector<Matrix>k);
    void  encrypt(char *m, size_t len);//加密
    void   decrypt( );//解密
    string getCipher();
    string getPlantext();
    string getDecryptedText();
    int getStart();
    int getEnd();
    vector<Matrix>getKey();//获取key
};

int main(int argc, const char * argv[]) {
    PSE pse;
    string M;
    pse.setTable(' ','~');
    cout<<"替换表为从\'"<<(char)pse.getStart()<<"\'到\'"<<(char)pse.getEnd()<<"\'的所有字符,长度为"<<pse.getEnd()-pse.getStart()+1<<endl;
    cout<<"替换表如下："<<endl;
    for (int i = pse.getStart(); i <= pse.getEnd(); ++i) {
        cout<<char(i)<<' ';
        if ((i-' ')%10==0){
            cout<<endl;
        }
    }
    cout<<endl;
    cout<<"密钥如下:"<<endl;
    cout<<"A: "<<endl;
    cout<<pse.getKey()[0]<<endl;
    cout<<"B: "<<endl;
    cout<<pse.getKey()[1]<<endl;
    cout<<"请输入明文：";
    getline(cin,M);
    pse.encrypt((char *)M.c_str(),strlen(M.c_str()));
    cout<<"密文为"<<pse.getCipher()<<endl;
    pse.decrypt();
    cout<<"解密此密文得："<<pse.getDecryptedText()<<endl;
    return 0;
}



vector<Matrix> PSE::getKey() {
    return key;
}
int PSE::getStart() {
    return start;
}

int PSE::getEnd() {
    return start+table_length-1;
}
void PSE::setTable(int start, int end) {
    this->start=start;
    table_length=end-start+1;
    generateKey();
}
void PSE::decrypt() {
    vector<int> tmp_c;
    decrypted_text.resize(cipher.size());
    tmp_c.resize(cipher.size());
    for (int i = 0; i < tmp_c.size(); ++i) {
        tmp_c[i]=cipher[i]-start;
    }



    for (int j = 0; j < tmp_c.size()/3; ++j) {
        Matrix C(3,1,table_length);

        for (int i = 0; i < 3; ++i) {
            C.setItem(i,0,tmp_c[j*3+i]);
        }

        Matrix tmp_1(C-key[1]);
        Matrix tmp_2(key[0].Inverse()*tmp_1);

        for (int k = 0; k < 3; ++k) {
            decrypted_text[j*3+k]=tmp_2.getItem(k,0)+start;
        }

    }

}
string PSE::getDecryptedText(){
    char tmp[decrypted_text.size()-plaintext_inteval];

    for (int i = 0; i < decrypted_text.size()-plaintext_inteval; ++i) {
        tmp[i]=decrypted_text[i];
    }

    return string(tmp,decrypted_text.size()-plaintext_inteval);
}
string PSE::getCipher() {
    char tmp[cipher.size()];
    for (int i = 0; i < cipher.size(); ++i) {
        tmp[i]=cipher[i];

    }

    return string(tmp,cipher.size());
}
string PSE::getPlantext(){
    char tmp[plaintext.size()];
    for (int i = 0; i < plaintext.size(); ++i) {
        tmp[i]=plaintext[i];
    }

    return string(tmp,plaintext.size());
}

void PSE::encrypt(char * m, size_t len) {

    plaintext.resize(len);

    for (int i = 0; i < plaintext.size(); ++i) {//存储到plaintext
        plaintext[i]=m[i];
    }
    vector<int> m_tmp;
    m_tmp.resize(len);
    for (int k = 0; k < len; ++k) {
        m_tmp[k]=m[k]-start;
    }

    plaintext_inteval=0;
    while (m_tmp.size()%3!=0){
        m_tmp.push_back(' ');
        plaintext_inteval++;
    }
    cipher.resize(m_tmp.size());


    Matrix tmp_M(3,1,table_length);

    for (int l = 0; l < m_tmp.size()/3; ++l) {
        for (int j = 0; j < 3; ++j) {
            tmp_M.setItem(j,0,m_tmp[j+l*3]);
        }

        Matrix tmp_1(key[0]*tmp_M);
        Matrix tmp_C(key[1]+tmp_1);

        for (int i = 0; i < 3; ++i) {

            cipher[l*3+i]=tmp_C.getItem(i,0)+start;
        }


    }

}

PSE::PSE(){
    key.resize(2);
    start=' ';
    table_length='~'-start+1;
    generateKey();
}

PSE::PSE(vector<Matrix>k) {
    start=' ';
    table_length='~'-start+1;
    setKey(k);
}

void PSE::setKey(vector<Matrix>k) {
    key[0].reinit(3,3,table_length);
    key[1].reinit(3,1,table_length);
    key[0]=k[0];
    key[1]=k[1];
}

bool PSE::isKeyValidate() {//检查key是否合法，只需要检查A
    return key[0].det()!=0&&Utils::gcd(key[0].det(),key[0].getP())==1;
}
void PSE::generateKey() {
    key[0].reinit(3,3,table_length);
    key[1].reinit(3,1,table_length);

    while (1){
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                key[0].setItem(i,j,Utils::generateRandomNum(0,table_length));
            }
        }



        if(isKeyValidate()){//检测key是否合法
            break;
        }

    }
    for (int i = 0; i < 3; ++i) {//B 无须检测,在start到end之间即可
        key[1].setItem(i,0,Utils::generateRandomNum(0,table_length));
    }


}
