
#ifndef _ZNXML_H_
#define _ZNXML_H_

#include <stdio.h>

#define XML_HEAD   ""   //ǰ׺
#define XML_LEFT   "<"   //������
#define XML_RIGHT  ">"   //������
#define XML_END    "/"   //������
#define XML_TAIL   ""    //��׺
#define XML_BR     "\r\n"  //�س���,�����ݶ��ûس�������

//����
/*
   XML_HEAD="#" XML_TAIL="@"
   XML_LEFT="<" XML_TAIL=">"
   XML_END="/" XM_BR="\r\n"

   ���ֶ�abc��ʽΪ
#<abc>@

#</abc>@
 */

//����һ���յ�xml�ļ�
int zn_openxmlfile(const char *filename,FILE **fp);

//��xml�ļ��ж�ȡ����,�ֶ���Ϊxmlname,dataΪ�������ݻ�����
int zn_readxmldata(FILE **fp,const char *xmlname,char *data);

//��xml�ļ��ж�ȡ��������,�ֶ���Ϊxmlname,ʧ�ܷ���-1
long zn_readxmllongdata(FILE **fp,const char *xmlname);

//��xml�ļ�д������,���������ᱻ����,dataΪ����,databr�����Ƿ�����ǰ���ûس���������,xmlbr�����Ƿ�����ݼ��ûس�������
int zn_writexmldata(FILE **fp,const char *xmlname,const char *data,int databr,int xmlbr);
//��xml�ļ�ɾ��һ���ֶ���Ϊxmlname����
int zn_deletexmldata(FILE **fp,const char *xmlname);

void zn_closexmlfile(FILE **fp);

#endif
