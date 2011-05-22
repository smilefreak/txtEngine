/**
 *  Parser code is not mine using freely distributed TinYXML library
 * @author James Boocock
 *
 **/

#include <iostream>
#include <sstream>
#include "tinyxml.h"
#include "World.h"

#define WORLD_ATTRIBUTES 3
#define AREA_ATTRIBUTES 2
#define STATE_DESCRIPTION_ATTRIBUTES 1
#define ITEM_ATTRIBUTES 1
#define PARSING_ERROR 2

World* world;

void error_parsing(std::string error_string);
StateDescriptor *make_state_descriptor(TiXmlNode *pDescription, const char *parent_id);

Item *make_item(TiXmlNode *pItem, int parent_id){
   TiXmlNode* pChild;
   const char *item_id, *error_tag;
   int attributesFound =0;
   bool has_id = false;
   Item *item;
   TiXmlElement *element = pItem->ToElement();
   TiXmlAttribute *attributes = element->FirstAttribute();
   while(attributes){
      if(!strcmp(attributes->Name(), "id")){
         item_id = attributes->Value();
         attributesFound++;
         has_id = true;
      } else {
         error_tag = attributes->Name();
         fprintf(stderr, "found something but shouldnt have in make_item.\n");
         attributesFound++;
      }
      attributes = attributes->Next();
   }
   if(ITEM_ATTRIBUTES == attributesFound && has_id){
      item = new Item(true, item_id);
      for ( pChild = pItem->FirstChild(); pChild != 0; pChild = pChild->NextSibling()){
         if(pChild->Type() == TiXmlNode::TINYXML_ELEMENT){
            if(!strcmp(pChild->Value(), "statedescriptor")){
               item->set_description(make_state_descriptor(pChild, item_id));
            }
         }
      }
   } else {
      std::ostringstream sin;
      sin << "Under parent ";
      sin << parent_id;
      sin << " there is an attribute error in an item, found: ";
      sin << error_tag;
      std::string message = sin.str();
      error_parsing(message);
   }
   return item;
}

StateDescriptor *make_state_descriptor(TiXmlNode *pDescription, const char *parent_id){
   TiXmlNode* pChild;
   const char *state_desc_id, *error_tag;
   int attributesFound = 0;
   bool has_id = false;
   StateDescriptor *state_descriptor;
   TiXmlElement *element = pDescription->ToElement();
   TiXmlAttribute *attributes = element->FirstAttribute();
   while(attributes){
      if(!strcmp(attributes->Name(), "id")){
         state_desc_id = attributes->Value();
         attributesFound++;
         has_id = true;
      } /*else if(!strcmp(attributes->Name(), "switch")){
         description_switch = attributes->Value();
         attributesFound++;
      }
        */
      else {
         error_tag = attributes->Name();
         fprintf(stderr, "found something but shouldnt have.\n");
         attributesFound++;
      }
      attributes = attributes->Next();
   }
   if(STATE_DESCRIPTION_ATTRIBUTES == attributesFound && has_id){
      state_descriptor = new StateDescriptor(state_desc_id);
      for ( pChild = pDescription->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) 
         {
            if(pChild->Type() == TiXmlNode::TINYXML_TEXT){
               state_descriptor->set_description(pChild->ToText()->Value());
            } else {
               std::ostringstream sin;
               sin << "Under parent ";
               sin << parent_id;
               sin << " there is a tag error in ";
               sin << state_desc_id;
               std::string message = sin.str();
               error_parsing(message);
            }
         }
   } else {
      std::ostringstream sin;
      sin << "Under parent ";
      sin << parent_id;
      sin << " there is an attribute error in a state descriptor, found: ";
      sin << error_tag;
      std::string message = sin.str();
      error_parsing(message);
   }

   return state_descriptor;
}

Area *make_area(TiXmlNode *pArea, int area_index) {
   TiXmlNode* pChild;
   int attributesFound = 0;
   const char *area_id = "invalid", *desc_id = "invalid", *error_tag;
   bool has_id = false, has_desc = false;
   Area *area;
   TiXmlElement *element = pArea->ToElement();
   TiXmlAttribute *attributes = element->FirstAttribute();
   while(attributes){
      if(!strcmp(attributes->Name(), "id")) {
         area_id = attributes->Value();
         attributesFound++;
         has_id = true;
      } else if (!strcmp(attributes->Name(), "initialdescription")){
         desc_id = attributes->Value();
         attributesFound++;
         has_desc = true;
      } else {
         error_tag = attributes->Name();         
      }
      attributes=attributes->Next();
   }  
   if(attributesFound == AREA_ATTRIBUTES && has_desc && has_id){
      area = new Area(area_id, desc_id);
      for ( pChild = pArea->FirstChild(); pChild != 0; pChild = pChild->NextSibling()){
         if(pChild->Type() == TiXmlNode::TINYXML_ELEMENT){
               if(!strcmp(pChild->Value(), "statedescriptor")){
                  area->add_description(make_state_descriptor(pChild, area_id));
               } else if(!strcmp(pChild->Value(), "item")){
                  std::cout << "Havn't implemented create item yet." << std::endl;
               } else if(!strcmp(pChild->Value(), "command")){
                  std::cout << "Havn't implemented create command yet" << std::endl;
               }               
         } else {
            std::ostringstream sin;
            sin << "Under area ";
            sin << area_index;
            sin << ", there is tag that doesn't go there found: ";
            sin << error_tag;
            std::string message = sin.str();
            error_parsing(message);
         }
      }
   } else {
       std::ostringstream sin;
       sin << "Under area ";
       sin << area_index;
       sin << " there is an attribute error, found: ";
       sin << error_tag;
       std::string message = sin.str();
       error_parsing(message);
   }

   return area;
}
void make_world(TiXmlNode *pParent){
   const char  *author = "invalid", *language = "invalid", *initialarea = "invalid";
   int attributesFound = 0, num_of_areas = 0;
   bool has_auth = false, has_lang = false, has_init = false;
   TiXmlNode* pChild;
   TiXmlElement *element = pParent->ToElement();
   TiXmlAttribute *attributes = element->FirstAttribute();
   while (attributes){
      if(!strcmp(attributes->Name(),"author")){
         author = attributes->Value();
         attributesFound++;
         has_auth = true;
      }
      else if(!strcmp(attributes->Name(),"language")){
         language = attributes->Value();
         attributesFound++;
         has_lang = true;
      }
      else if(!strcmp(attributes->Name(),"initialarea")){
         initialarea = attributes->Value();
         attributesFound++;
         has_init = true;
      }
      attributes=attributes->Next();
   }
   if(attributesFound == WORLD_ATTRIBUTES && has_init && has_lang && has_auth){
      world = new World(author, language, initialarea);
      for ( pChild = pParent->FirstChild(); pChild != 0; pChild = pChild->NextSibling()){
         if(pChild->Type() == TiXmlNode::TINYXML_ELEMENT){
            if(!strcmp(pChild->Value(),"area")){
               num_of_areas++;
               world->add_area(make_area(pChild, num_of_areas));
            }
         } else {
            error_parsing("ignoring a tag below world, its not an area.");
         }
      }
   }else{
      error_parsing("one or more of the attributes required for world are missing");
   }
}

void error_parsing(std::string message){
   const char *error_string = message.c_str();
   fprintf(stderr,"ERROR: [%s]\n", error_string);
   exit(2);
}


void make_objects( TiXmlNode* pParent, unsigned int indent = 0 )
{
   if ( !pParent ) return;
   TiXmlNode* pChild; 
   pParent = pParent->FirstChild();
   pChild = pParent->NextSibling();
   int t = pChild->Type();
   std::cout << t << std::endl;
   if(t == TiXmlNode::TINYXML_ELEMENT){
      make_world(pChild);
 }
}
// load the named file and dump its structure to STDOUT

void make_objects(const char* pFilename)
{
   TiXmlDocument doc(pFilename);
   bool loadOkay = doc.LoadFile();
   if (loadOkay)
      {
         printf("\n%s:\n", pFilename);
        make_objects( &doc ); // defined later in the tutorial
      }
   else
      {
         printf("Failed to load file \"%s\"\n", pFilename);
      }
}

void print_world_tree(){
   std::ostringstream sin;
   sin << "World:\n";
   for(int area = 0; area < 
   std::string message = sin.str();
   error_parsing(message);
}

int main(int argc, char** argV)
{
   make_objects("testInput.xml");
   /*delete world deletes everything, as the the deconstructor for
     world calls the decontructor for all areas, which calls the
     decontructor for all items and descriptions...
    */
   print_world_tree();
   delete world;
   return 0;
}
