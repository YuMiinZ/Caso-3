/*

Caso 3
Fiorella Zelaya
Ericka Yu Min Guo Chen

*/

//Inclusion of libraries
#include "rapidxml/rapidxml_ext.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include "IObserverPattern.hpp"
#include "AnimatorGenerator.hpp"
#include "Selection.hpp"
#include "Routing.hpp"
#include "Generation.hpp"
#include <queue>


using namespace std;


int main()
{

   int frames = 20;
   int degrees = 230;
   double height;
   double width;
   string fileName = "Images/bird.svg";

   AnimatorGenerator *animator = new AnimatorGenerator();
   Selection *selection = new Selection();
   Routing *routing = new Routing();
   Generation *generation = new Generation();

   selection->attach(animator);
   routing->attach(animator);
   generation->attach(animator);

   animator->setSelection(selection);
   animator->setGeneration(generation);
   animator->setRouting(routing);

    SVG svgDetails;
    svgDetails.setFrames(frames);
    svgDetails.setDegrees(degrees);

    xml_document<> document;
    char* svgFileName = new char[fileName.size() + 1];  // Create char buffer to store string copy
    strcpy (svgFileName, fileName.c_str());
    file<> file(svgFileName);
    document.parse<0>(file.data());

    if(document.first_node()->first_attribute("height")){
        height = stod(document.first_node()->first_attribute("height")->value());
        svgDetails.setHeight(height);
    }
    if(document.first_node()->first_attribute("width")){
        width = stod(document.first_node()->first_attribute("width")->value());
        svgDetails.setWidth(width);
    }

    if((int)svgDetails.getHeight() == 0 || (int)svgDetails.getWidth() == 0 || document.first_node()->first_attribute("viewBox")->value() != ""){
        string viewBox = document.first_node()->first_attribute("viewBox")->value();
        string viewBoxParameter[4];
        int i = 0;
        stringstream ssin(viewBox);
        while (ssin.good() && i < 4){
            ssin >> viewBoxParameter[i];
            ++i;
        }
        for(i = 0; i < 4; i++){
            cout << viewBoxParameter[i] << endl;
        }
        height = stod(viewBoxParameter[2]);
        width = stod(viewBoxParameter[3]);
        svgDetails.setHeight(height);
        svgDetails.setWidth(width);

    }

    svgDetails.setDoc(&document);
    svgDetails.setFileName(fileName);

    vector<string> colors = {"#00E4FF", "#FF00B9", "#FFE800", "#F7FF00", "#00FF1A", "#FF0101" , "#FF8101", "#FFFFFF"};
    vector<vector<double>> positions = {{406, 270}, {500, 600}, {730, 32}, {466, 3687}, {2295, 2676}, {1000, 1800}, {2645, 1820}, {160, 464}, {200, 500}, {400, 200}, {264.013,440}, {500,500}};
    animator->start(document.first_node(), colors, positions, svgDetails);

    delete(animator);
    delete(selection);
    delete(routing);
    delete(generation);


    return 0;
}
