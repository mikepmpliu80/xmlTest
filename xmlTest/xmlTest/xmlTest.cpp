#include <string>
#include "tinyxml.h"  
#include "tinystr.h"

using namespace std;

class Person{
public:
    string  m_Name;
    string  m_Gender;
    int     m_Age;
};
void SaveXml(Person* person, string file);
void LoadXml(string file, Person* person);


int main(){
	string file = "Person.xml";
    Person Michael;
    Michael.m_Name = "Mike";
    Michael.m_Gender = "Male";
    Michael.m_Age = 28;
    SaveXml(&Michael, file);
    LoadXml(file, &Michael);
    printf("名字: %s\r\n", Michael.m_Name.c_str());
    printf("性別: %s\r\n", Michael.m_Gender.c_str());
    printf("年齡: %d\r\n", Michael.m_Age);
	system("PAUSE");
    return 0;
}

void SaveXml(Person* person, string file){  
	TiXmlDocument xmlDoc;
	TiXmlNode *rootElement = xmlDoc.InsertEndChild(TiXmlElement("Person"));
	rootElement->InsertEndChild(TiXmlElement("Name"))->InsertEndChild(TiXmlText(person->m_Name.c_str()));
    rootElement->InsertEndChild(TiXmlElement("NickName"))->InsertEndChild(TiXmlText(person->m_Gender.c_str()));

    char dest[10];
	sprintf(dest,"%d",person->m_Age);
    rootElement->InsertEndChild(TiXmlElement("Age"))->InsertEndChild(TiXmlText(dest));
    xmlDoc.SaveFile(file.c_str());
}

void LoadXml(string file, Person* person){  
    TiXmlDocument xmlDoc(file.c_str());
    xmlDoc.LoadFile();
    if(xmlDoc.ErrorId() > 0)
        return;

    TiXmlElement* pRootElement = xmlDoc.RootElement();
    if(!pRootElement)
        return;

    TiXmlElement* pNode = NULL;
    pNode = pRootElement->FirstChildElement("Name");
    if(pNode){
		person->m_Name = pNode->GetText();      
    }
    pNode = pRootElement->FirstChildElement("NickName");
    if(pNode){
        person->m_Gender = pNode->GetText();      
    }
    pNode = pRootElement->FirstChildElement("Age");

    if(pNode)
    {
        person->m_Age = atoi(pNode->GetText());     
    }

}