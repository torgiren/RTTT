#include "text.h"

Text::Text():
	id(0), x(0), y(0), z(0), px(0.0f), py(0.0f), alpha(255), font(NULL), text(NULL), upd(1), w(SCREENWIDTH), h(SCREENHEIGHT), nlSize(16), spSize(8), tabSize(32), align(LEFT)
	{
	//setSprite(NULL);
	//setStr("");
	};


Text::Text(unsigned int id, float x, float y, float z, float px, float py, Sprite *sSprite, const char *sText, unsigned int w, unsigned int h, int nlSize, int spSize, int tabSize):
	id(id), x(x), y(y), z(z), px(px), py(py), alpha(255), font(NULL), text(NULL), upd(1), w(w), h(h), nlSize(nlSize), spSize(spSize), tabSize(tabSize), align(LEFT)
	{
	setSprite(sSprite);
	setStr(sText);
	}

Text::Text(const Text& txt):
	id(txt.id), x(txt.x), y(txt.y), z(txt.z), px(txt.px), py(txt.py), alpha(255), font(NULL), text(NULL), upd(1), w(txt.w), h(txt.h), nlSize(txt.nlSize), spSize(txt.spSize), tabSize(txt.tabSize), align(LEFT)
	{
	setSprite(txt.font);
	setStr(txt.text);
	}

Text::~Text()
	{
	if(text)
		delete [] text;
	}

/********** Sety/gety ***************************/
void Text::setSprite(Sprite *sSprite)
	{
	font=sSprite;
	}

void Text::setStr(const char *sStr)
	{
	if(!sStr)
		{
		printf("FAIL: Text.setStr: NULL str\n");
		return;
		}
	if(text)
		delete [] text;
	try
		{
		text=new char[strlen(sStr)+1];
		}
	catch(bad_alloc &)
		{
		printf("FAIL: Text.setStr: Nie udalo sie zajac pamieci na tekst\n");
		return;
		}
	sprintf(text, "%s", sStr);
	upd=1;
	}

void Text::addStr(const char *sStr)
	{
	if(!sStr)
		{
		printf("FAIL: Text.setStr: NULL str\n");
		return;
		}
	if(!text)
		{
		setStr(sStr);
		return;
		}
	char *tmp=NULL;
	try
		{
		tmp=new char[strlen(text)+strlen(sStr)+1];
		}
	catch(bad_alloc &)
		{
		printf("FAIL: Text.setStr: Nie udalo sie zajac pamieci na tekst\n");
		return;
		}
	sprintf(tmp, "%s%s", text, sStr);
	if(text)
		delete [] text;
	text=tmp;
	upd=1;
	}

void Text::update()
	{
	if(!font)
		return;
	if(upd && text /*&& text[0]!='\0'*/)
		{
		//
		}
	}

void Text::print()
	{
	if(!font)
		return;
	//update();

	upd=0;
	int cx=x, cy=y;
	unsigned int len=strlen(text);
	if(align==CENTER)
		cx=x+(int)w/2-getLineLen(text)/2;
	else if(align==RIGHT)
		cx=x+(int)w-getLineLen(text)-1;
	//unsigned int wlen=getWordLen(text);
	for(unsigned int i=0; i<len; i++)
		{
		unsigned char c=text[i];
		if(c==' ')
			cx+=spSize;
		else if(c=='\t')
			cx=((cx/tabSize)+1)*tabSize;
		else if(c=='\r');
		else if(c=='\n');
		else if(c<' ')// || c>font->getAnimCount()+' ')
			cx+=spSize;
		else
			{
			//printf("> %c , %d, %d\n", text[i], cx, cy);
			font->print(cx, cy, z, c-' ', 0, alpha);
			cx+=font->getAnim(c-' ').getFrame(0).w+1;
			}
		if(c=='\n' || cx>=(int)w || ((c=='\t' || c=='\n' || c==' ') && cx+getWordLen(text+i+1)>x+(int)w))
			{
			cx=x;
			cy+=nlSize;
			if(align==CENTER)
				cx=x+(int)w/2-getLineLen(text+i)/2;
			else if(align==RIGHT)
				cx=x+(int)w-getLineLen(text+i)-1;
			if((unsigned int)abs(cy-y)>=h)
				h+=nlSize;
			}
		}
	}

/********** Rozne **********/
int Text::getWordLen(const char *str)		// Zwraca dlugosc najblizszego slowa w pixelach
	{
	if(!font)
		return 0;
	int i=0;
	int len=0;
//	bool start=0;
	while(str && str[i])
		{
		if(str[i]<=' ')
			{
			i++;
//			if(start)
				break;
//			else
//				continue;
			}
//		else
//			start=1;
		len+=font->getAnim(str[i]-' ').getFrame(0).w+1;
		i++;
		}
	return len;
	}

int Text::getLineLen(const char *str)		// Zwraca dlugosc linii w pixelach
	{
	if(!font)
		return 0;
	int i=0;
	int len=0;
	bool start=0;
	while(str && str[i])
		{
		unsigned char c=str[i];
		if(c=='\n' || c=='\r')
			{
			i++;
			if(start)
				{
//				while(str && str+i>str)
//					{
//					i--;
//					if(str[i]==' ')
//						len-=spSize;
//					else if(str[i]=='\t')
//						len-=tabSize;
//					else
//						break;
//					}
				break;
				}
			else
				continue;
			}
		else
			start=1;
		if(c==' ')
			len+=spSize;
		else if(c=='\t')
			len+=/*((len/tabSize)+1)* */tabSize;
		else if(c<' ' || c>=font->getAnimCount()+' ')
			len+=spSize;
		else
			len+=font->getAnim(c-' ').getFrame(0).w+1;
		i++;
		}
	return len;
	}
