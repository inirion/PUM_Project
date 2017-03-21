#include "Lang.hpp"
#include <iterator>

sf::String s2ws(std::string str){	//Zamiana std::string na sf::String UTF32
	sf::String ws;
	std::basic_string < sf::Uint32 > tmp;
	sf::Utf8::toUtf32( str.begin(), str.end(), std::back_inserter( tmp ) );
	ws = tmp;

	return ws;
}
std::string ws2s(sf::String str){
	std::string s;
	sf::Utf32::toUtf8(str.begin(), str.end(), std::back_inserter(s));

	return s;
}


bool Lang::inited=false;

size_t Lang::deflang=0;
size_t Lang::selected=0;

std::vector<std::string> Lang::languages;
std::map<std::string, std::string> Lang::m;


void Lang::init(){
	if(!inited){
		inited=true;

		sf::String p;

#define DB(id, str) m[p+id]=str;

		#include "lang/pl.inc"
		languages.push_back(p);

		#include "lang/en.inc"
		languages.push_back(p);
	}
}

std::string Lang::translateRaw(std::string in){
	std::string out;

	if(m.find(languages[selected]+in)!=m.end()){
		out=m.at(languages[selected]+in);
	}else if(m.find(languages[deflang]+in)!=m.end()){
		out=m.at(languages[deflang]+in);
	}else{
		out=in;
	}

	return out;
}

sf::String Lang::translate(std::string in){
	/*
	std::string out;

	if(m.find(languages[selected]+in)!=m.end()){
		out=m.at(languages[selected]+in);
	}else if(m.find(languages[deflang]+in)!=m.end()){
		out=m.at(languages[deflang]+in);
	}else{
		out=in;
	}

	return s2ws(out);
	*/
	return s2ws(translateRaw(in));
}

std::string lineScroll(std::string str,const unsigned int first, const unsigned int last){
	size_t nfound=0;
	for(unsigned int i=0; i<first; i++){
		nfound=str.find('\n',1);
		if(nfound==std::string::npos) break;
		str.erase(0,nfound);
	}

	if(last!=0){
		const unsigned int diff=last-first;
		for(unsigned int i=0; i<diff; i++){
			nfound=str.find('\n',nfound+1);
			if(nfound==std::string::npos) break;
		}
		if(nfound!=std::string::npos) str.erase(nfound);
	}
	return str;
}

void formatText(sf::Text &text, sf::FloatRect rect){
	std::string toformat=ws2s(text.getString());

	size_t found=-1,bfound=0,spacefound;
	unsigned int lines=1;

	do{
		found=toformat.find('\n',found+1);
		if(found!=std::string::npos) toformat.replace(found,1," ");
		else break;
	}while(true);

	found=-1;
	do{
		found=toformat.find("  ",found+1);
		if(found!=std::string::npos) toformat.replace(found,2," ");
		else break;
	}while(true);

	found=-1;
	do{
		found=toformat.find("[br]",found+1);
		if(found!=std::string::npos) toformat.replace(found,4,"\n");
		else break;
	}while(true);

	std::string formated,line;
	found=toformat.find(' ');

	while(found!=std::string::npos){
		line+=toformat.substr(bfound,found-bfound);
		bfound=found;
		found=toformat.find(' ',found+1);

		text.setString((line));
		if(text.getGlobalBounds().width>rect.width){
			formated+=line;
			spacefound=formated.rfind(' ');
			line=formated.substr(spacefound+1);
			formated.erase(spacefound+1);
			formated.append(1,'\n');
			lines++;
		}
	}
	line+=toformat.substr(bfound,toformat.size()-bfound);

	text.setString((line));
	if(text.getGlobalBounds().width>rect.width){
		spacefound=line.rfind(' ');
		line.insert(spacefound+1,1,'\n');
		lines++;
	}
	formated+=line;

	text.setString(s2ws(formated));

	while(text.getGlobalBounds().height > rect.height){
		text.setString(s2ws(lineScroll(formated,0,--lines)));
		if(lines==0) break;
	}
}
