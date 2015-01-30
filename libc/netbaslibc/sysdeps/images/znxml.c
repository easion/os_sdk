 
#include "znxml.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <netbas/netbas.h>

//比较字符串,不区分大小写
int strcmpnocase(const char *str1,const char *str2)
{
	int i,len1,len2;

	len1=strlen(str1);
	len2=strlen(str2);

	if(len1!=len2) return 0;

	for(i=0;i<len1;i++)
	{
		if(toupper(str1[i])!=toupper(str2[i]))
				return 0;
	}

	return 1;
}

//生成XML标题,flag=0表示头,flag=1表示尾
void MakeXmlCaption(const char *varname,int flag,char *data)
{
	strcpy(data,"");

	strcat(data,XML_HEAD); //前缀
	strcat(data,XML_LEFT); //左括号

	if(flag)  strcat(data,XML_END);;//结束符

	strcat(data,varname);//字段名
	
	strcat(data,XML_RIGHT); //右括号
	strcat(data,XML_TAIL); //后缀
}


int zn_openxmlfile(const char *filename,FILE **fp)
{
	*fp=(void*)fopen(filename,"rb+");
	if(*fp==NULL) *fp=(void*)fopen(filename,"wb+");
	if(*fp==NULL) return 0;

	return 1;
}

int zn_findxmlpos(FILE **fp,const char *xmlname,int flag)
{
	FILE *pFile;
	int ch;
	int len;
	char strXml[255];
	char data[255];

	if(*fp==NULL) return -1;

	pFile=(FILE*)(*fp);
	rewind(pFile);
	MakeXmlCaption(xmlname,flag,strXml);
	len=strlen(strXml);

	while(!feof(pFile))
	{
		ch=0;
		//查找XML_HEAD
		while(toupper(ch)!=toupper(strXml[0]) && !feof(pFile))
			ch=fgetc(pFile);
		
		if(feof(pFile)) return -1;
		
		//已找到XML_HEAD
		memset(data,0,sizeof(data));
		if(len-1!=(int)fread(data,sizeof(char),len-1,pFile))
			return -1;
		//如果后面的字符串也相同
		if(strcmpnocase(strXml+1,data))
		{
			if(!flag)
				return ftell(pFile)-len;
			else
				return ftell(pFile)-1;
		}
		else
			fseek(pFile,1-len,SEEK_CUR);
	}

	return -1;
}

#if defined(__WIN32__)
//mingw没有这个函数
int ftruncate(int fd, off_t where)
{
 //errno=EPERM;
 return -1;
}
#endif

//删除文件数据,指针从pos1到pos2
int zn_deletefiledata(FILE **fp,long pos1,long pos2)
{
	FILE *pFile;
	long len;
	char data[256];
	
	if(*fp==NULL) return 0;
	if(pos1==-1 || pos2==-1) return 0;
	
	pFile=(FILE*)(*fp);
	if(pos1<0 || pos2<0 || pos2<pos1) return 0;

	while(1)
	{
		fseek(pFile,pos2+1,SEEK_SET);
		len=fread(data,sizeof(char),256,pFile);
		if(len<=0) break;
		pos2+=len;

		fseek(pFile,pos1,SEEK_SET);
		fwrite(data,sizeof(char),len,pFile);
		pos1+=len;
	}

	//截除文件尾数据
	ftruncate(fileno(pFile),pos1);

	fflush(pFile);

	return 1;
}

int zn_insertfiledata(FILE **fp,long pos,long size)//插入若干个空字节
{
	FILE *pFile;
	long rec;
	char data[256];
	long pos1,pos2;
	int i;

	if(*fp==NULL) return 0;
	if(pos<0) return 0;
	
	pFile=(FILE*)(*fp);

	//增加文件尾数据
	fseek(pFile,0,SEEK_END);
	pos2=ftell(pFile);

	for(i=0;i<size;i++) fputc(0,pFile);

	if(pos2-256<pos)
	{
		rec=pos2-pos;
		pos2=pos;
	}
	else 
	{
		rec=256;
		pos2-=256;
	}

	pos1=pos2+size;

	while(1)
	{
		fseek(pFile,pos2,SEEK_SET);
		fread(data,sizeof(char),rec,pFile);

		fseek(pFile,pos1,SEEK_SET);
		fwrite(data,sizeof(char),rec,pFile);
		
		if(pos2==pos) break;

		if(pos2-256<pos) 
		{
			rec=pos2-pos;
			pos2=pos;
		}
		else 
		{
			rec=256;
			pos2-=256;
		}

		pos1=pos2+size;
	}

	fflush(pFile);

	return 1;
}

int zn_readxmldata(FILE **fp,const char *xmlname,char *data)
{
	FILE *pFile;
	long pos1,pos2;
	int i;char *p;
	char strXml[256];

	if(*fp==NULL) return -1;
	
	pos1=zn_findxmlpos(fp,xmlname,0);
	if(pos1==-1) return 0;
	pos2=zn_findxmlpos(fp,xmlname,1);
	if(pos2==-1) return 0;
	
	pFile=(FILE*)(*fp);
	fseek(pFile,pos1,SEEK_SET);

	for(i=0;i<pos2-pos1+1 && !feof(pFile);i++)
	{
		data[i]=fgetc(pFile);
	}

	data[i]='\0';

	//清除XML头和尾

	MakeXmlCaption(xmlname,0,strXml);
	p=strstr(data,strXml);//找开始标识的右括号和后缀
	strcpy(data,p+strlen(strXml));

	MakeXmlCaption(xmlname,1,strXml);
	p=strstr(data,strXml);//找结束标识的右括号
	*p='\0';

	//清除前后回车符
	p=data;
	while(*p==0x0d || *p==0x0a) p++;
	strcpy(data,p);

	for(i=strlen(data)-1;i>=0;i--)
	{
		if(data[i]==0x0d || data[i]==0x0a)
			data[i]='\0';
		else
			break;
	}

	return 1;
}

long zn_readxmllongdata(FILE **fp,const char *xmlname)
{
	char data[255];

	if(zn_readxmldata(fp,xmlname,data))
		return atol(data);
	else
		return -1;
}

int zn_writexmldata(FILE **fp,const char *xmlname,const char *data,int databr,int xmlbr)
{
	FILE *pFile;
	long pos,pos1,pos2;
	int len,len1,len2;
	char strXml[64];
	char buf1[256],buf2[256];

	if(*fp==NULL) return -1;
	
	pos1=zn_findxmlpos(fp,xmlname,0);
	pos2=zn_findxmlpos(fp,xmlname,1);
	
	len=strlen(data);
	pFile=(FILE*)(*fp);
	
	if(pos1==-1 || pos2==-1)//如果不存在则新建
	{
		fseek(pFile,0,SEEK_END);//移动文件指针至末尾

		MakeXmlCaption(xmlname,0,strXml);//产生xml头
		fwrite(strXml,sizeof(char),strlen(strXml),pFile);//写入xml头
		if(databr) fwrite(XML_BR,sizeof(char),strlen(XML_BR),pFile);//写入回车符
		fwrite(data,sizeof(char),len,pFile);//写入数据
		if(databr) fwrite(XML_BR,sizeof(char),strlen(XML_BR),pFile);//写入回车符
		MakeXmlCaption(xmlname,1,strXml);//产生xml尾
		fwrite(strXml,sizeof(char),strlen(strXml),pFile);//写入xml尾
		fwrite(XML_BR,sizeof(char),strlen(XML_BR),pFile);//写入回车符
		if(xmlbr) fwrite(XML_BR,sizeof(char),strlen(XML_BR),pFile);//写入回车符

		fflush(pFile);
	}
	else//已存在,进行修改
	{
		pos=pos1;//保存新数据的指针位置
		len1=pos2-pos1+1;

		//生成xml数据首尾
		MakeXmlCaption(xmlname,0,strXml);//产生xml头
		strcpy(buf1,strXml);
		if(databr) strcat(buf1,XML_BR);//写入回车符

		if(databr) 
			strcpy(buf2,XML_BR);//写入回车符
		else 
			strcpy(buf2,"");
		MakeXmlCaption(xmlname,1,strXml);//产生xml尾
		strcat(buf2,strXml);

		len2=strlen(buf1)+len+strlen(buf2);

		if(len1==len2)//如果长度没改变，不需移指针
		{
			fseek(pFile,pos,SEEK_SET);//移动文件指针

			fwrite(buf1,sizeof(char),strlen(buf1),pFile);//写入xml头
			fwrite(data,sizeof(char),len,pFile);//写入新的数据
			fwrite(buf2,sizeof(char),strlen(buf2),pFile);//写入xml尾
		}
		else
		{
			if(len2<len1)//长度减少
			{
				fseek(pFile,pos,SEEK_SET);//移动文件指针

				fwrite(buf1,sizeof(char),strlen(buf1),pFile);//写入xml头
				fwrite(data,sizeof(char),len,pFile);//写入新的数据
				fwrite(buf2,sizeof(char),strlen(buf2),pFile);//写入xml尾

				pos1=ftell(pFile);
				zn_deletefiledata(fp,pos1,pos2);//截除文件尾数据
			}
			else//长度增加
			{
				zn_insertfiledata(fp,pos2+1,len2-len1);//插入字节到文件
				fseek(pFile,pos,SEEK_SET);//移动文件指针

				fwrite(buf1,sizeof(char),strlen(buf1),pFile);//写入xml头
				fwrite(data,sizeof(char),len,pFile);//写入新的数据
				fwrite(buf2,sizeof(char),strlen(buf2),pFile);//写入xml尾
			}
		}

		fflush(pFile);
	}

	return 1;
}

int zn_deletexmldata(FILE **fp,const char *xmlname)
{
	FILE *pFile;
	long pos1,pos2;
	int l=0,ch;

	if(*fp==NULL) return -1;
	
	pos1=zn_findxmlpos(fp,xmlname,0);
	pos2=zn_findxmlpos(fp,xmlname,1);
	
	pFile=(FILE*)(*fp);

	//计算要删除多余的回车符字节数
	fseek(pFile,pos2+1,SEEK_SET);
	ch=fgetc(pFile);

	while(ch==0x0d || ch==0x0a)
	{
		l++;
		ch=fgetc(pFile);
	}

	pos2+=l;
	
	if(pos1!=-1 && pos2!=-1)//如果存在
		zn_deletefiledata(fp,pos1,pos2);//截除文件尾数据
	else 
		return 0;

	return 1;
}

void zn_closexmlfile(FILE **fp)
{
	if(*fp!=NULL)
	{
		fclose(*fp);
		*fp=NULL;
	}
}
