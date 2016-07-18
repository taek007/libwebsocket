#include <openssl/des.h>
#include <stdio.h>
#include <string.h>
const char base[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/="; 
char* base64_encode(const char* data, int data_len); 
char *base64_decode(const char* data, int data_len); 

void main() 
{
 // TODO: Add your control notification handler code here
 DES_cblock key;

 unsigned char key_hex[256] = {0};
 unsigned char data_hex[256] = {0};
 unsigned char initval_hex[256] = {0};
 unsigned char temp[256] = {0};
 int i = 0;
 int keylen = 0;
 int datalen = 0;
 int InitialLen = 0;
 DES_key_schedule schedule;
 DES_key_schedule schedule2;
 DES_key_schedule schedule3;
 const_DES_cblock input;
 DES_cblock output;
 DES_cblock ivec;

    UpdateData(TRUE);

 m_key.Remove(' ');
 m_data.Remove(' ');
 m_initval.Remove(' ');
 
 keylen = m_key.GetLength()/2;
    datalen = m_data.GetLength()/2;
 InitialLen = m_initval.GetLength()/2;

 if (keylen%8!=0)
 {
  AfxMessageBox("输入密钥长度不是8的整数倍，请重新输入!");
  return; 
 }

 if (datalen%8!=0)
 {
  AfxMessageBox("输入数据长度不是8的整数倍，请重新输入!");
  return; 
 }

 StrToHex(m_key,key_hex,keylen);
 StrToHex(m_data,data_hex,datalen);
 StrToHex(m_initval,initval_hex,InitialLen);

 

//单DES密钥设置

 if (keylen == 8)
 {
  memcpy(key,key_hex,keylen);
  DES_set_key_unchecked(&key, &schedule); 
 }

//三DES密钥设置
 else if (keylen == 16)
 {
  memcpy(key,key_hex,8);
        DES_set_key_unchecked(&key, &schedule); 
  memcpy(key,key_hex+8,8);
        DES_set_key_unchecked(&key, &schedule2); 
  memcpy(key,key_hex,8);
        DES_set_key_unchecked(&key, &schedule3); 
 }
    
 
 memcpy(ivec,initval_hex,InitialLen);

 //单DES算法
 if (keylen == 8)
 {
  //ECB模式
        if (((CButton*)GetDlgItem(IDC_RADIO1))->GetCheck())
  {
   for(i = 0;i < datalen/8;i++)
   {
    memcpy(input,data_hex+i*8,8);
    DES_ecb_encrypt(&input, &output, &schedule, DES_ENCRYPT);
    memcpy(temp+i*8,output,8);
   }
  }
  //CBC模式
  else if (((CButton*)GetDlgItem(IDC_RADIO2))->GetCheck())
  {
   for(i = 0;i < datalen/8;i++)
   {
    DES_ncbc_encrypt(data_hex+i*8, temp+i*8,8,&schedule,&ivec, DES_ENCRYPT);
   }
  }
 }
 //TDES算法
 else if (keylen == 16)
 {
  //ECB模式
        if (((CButton*)GetDlgItem(IDC_RADIO1))->GetCheck())
  {
   for (i = 0;i < datalen/8;i++)
   {
    memcpy(input,data_hex+i*8,8);
    DES_ecb3_encrypt(&input, &output, &schedule, &schedule2, &schedule3, DES_ENCRYPT);
    memcpy(temp+i*8,output,8);
   }
   
  }
  //CBC模式
  else if (((CButton*)GetDlgItem(IDC_RADIO2))->GetCheck())
  {
   for(i = 0;i < datalen/8;i++)
   {
    DES_ede3_cbc_encrypt(data_hex+i*8, temp+i*8,8,&schedule, &schedule2, &schedule3,&ivec, DES_ENCRYPT);
   }
  }

 }
 
 HexToStr(temp,datalen,m_result);

    UpdateData(FALSE);
}