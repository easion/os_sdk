
#ifndef _ZNXML_H_
#define _ZNXML_H_

#include <stdio.h>

#define XML_HEAD   ""   //前缀
#define XML_LEFT   "<"   //左括号
#define XML_RIGHT  ">"   //右括号
#define XML_END    "/"   //结束符
#define XML_TAIL   ""    //后缀
#define XML_BR     "\r\n"  //回车符,各数据段用回车符隔开

//例如
/*
   XML_HEAD="#" XML_TAIL="@"
   XML_LEFT="<" XML_TAIL=">"
   XML_END="/" XM_BR="\r\n"

   则字段abc格式为
#<abc>@

#</abc>@
 */

//创建一个空的xml文件
int zn_openxmlfile(const char *filename,FILE **fp);

//从xml文件中读取数据,字段名为xmlname,data为接受数据缓冲区
int zn_readxmldata(FILE **fp,const char *xmlname,char *data);

//从xml文件中读取长整数据,字段名为xmlname,失败返回-1
long zn_readxmllongdata(FILE **fp,const char *xmlname);

//向xml文件写入数据,如果存在则会被覆盖,data为数据,databr决定是否数据前后用回车条符隔开,xmlbr决定是否各数据间用回车符隔开
int zn_writexmldata(FILE **fp,const char *xmlname,const char *data,int databr,int xmlbr);
//从xml文件删除一段字段名为xmlname数据
int zn_deletexmldata(FILE **fp,const char *xmlname);

void zn_closexmlfile(FILE **fp);

#endif
