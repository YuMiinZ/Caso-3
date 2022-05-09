#ifndef __SELECTION_HEADER__
#define __SELECTION_HEADER__

#include <thread>
#include <list>
#include <vector>
#include <sstream>
#include "main.hpp"
#include "SvgElements.hpp"
#include <iostream>
#include <string>

class Selection: public Subject{
private:
    Observer* animator;
    vector<Element*> selectedElements;

public:
    Selection() = default;
    ~Selection(){}
    void attach(Observer* pAnimator){
        animator=pAnimator;
    }
    void detach(Observer* pWhichElement){

    }
    void notify(void* pCode){
        animator->update(pCode);
    }

    vector<int> colorConverterHexToRBG(char const*pHexColor){
        /*
        Functioning: Converts a color from hexadecimal to RGB.

        Input:
        -pHexColor(chat const*): Color in hexadecimal.

        Output:
        -Returns a vector with the colors red, green, and blue of the converted hex color.

        */
        int curso = 2;
        int* cursoPointer = &curso;
        int red, green, blue;
        sscanf(pHexColor, "#%02x%02x%02x", &red, &green, &blue);
        return {red,green,blue};
    }

    vector<Element*> getSelectedElements(){
        /*
        Functioning: Returns the list of selected elements.

        Input: N/A

        Output
        -selectedElements(vector<Element*>) Vector of elements that matched based on their color and point.
        */
        return selectedElements;
    }

    void setSelectedElements(vector<Element*> pNewSelectedElements){
        /*
        Functioning: Save all the selected elements in the variable of the selectedElements class.

        Input:
        -pNewSelectedElements(vector<Element*>): Selected elements

        Output: N/A
        */
        selectedElements = pNewSelectedElements;
    }

    vector<vector<double>> getPoints(string pPoints){
        /*
        Functioning: Gets the points of the polyline and polygon elements

        Input:
        -pPoints(string): String of the points to get.

        Output:
        -vectorPoints(vector<vector<double>>): Points xy obtained from the string.
        */
        vector<vector<double>> vectorPoints;
        vector<double> vectorXYPoints;
        while(!pPoints.empty()){
            vectorXYPoints.push_back(stoi(pPoints.substr(0, pPoints.find(","))));
            pPoints.erase(0,pPoints.find(",")+1);
            if(pPoints.find(" ")!= string::npos){
                vectorXYPoints.push_back(stoi(pPoints.substr(0, pPoints.find(" "))));
                pPoints.erase(0,pPoints.find(" ")+1);
            }
            else{
                vectorXYPoints.push_back(stoi(pPoints.substr(0, pPoints.length())));
                pPoints.erase(0,pPoints.length());
            }
            vectorPoints.push_back(vectorXYPoints);
            vectorXYPoints.clear();
        }
        return vectorPoints;
    }

    void getMaxMinValues(double& pMaxXValue, double& pMinXValue, double& pMaxYValue, double& pMinYValue,vector<vector<double>>pPoints){
        /*
        Functioning: Get the min and max xy points of the list of points.

        Input:
        -pMaxXValue
        -pMinXValue
        -pMaxYValue
        -pMinYValue
        -pPoints

        Output: N/A

        */
        pMaxYValue=pPoints[0][1], pMaxXValue=pPoints[0][0], pMinYValue=pPoints[0][1], pMinXValue=pPoints[0][0];
        for(int posicion=0;posicion<pPoints.size();posicion++){
            pMaxYValue=((pPoints[posicion][1]>=pMaxYValue)?pPoints[posicion][1]:pMaxYValue);
            pMinYValue=((pPoints[posicion][1]<=pMinYValue)?pPoints[posicion][1]:pMinYValue);
            pMaxXValue=((pPoints[posicion][0]>=pMinXValue)?pPoints[posicion][0]:pMaxXValue);
            pMinXValue=((pPoints[posicion][0]<=pMinXValue)?pPoints[posicion][0]:pMinXValue);
        }

    }

    void getMoveValues(double& pXvalue, double& pYValue, string pPath){
        /*
        Functioning: Extracts the xy values of the Move command from the path.

        Input:
        -pXvalue
        -pYValue
        -pPath

        Output: N/A

        */
       try
       {
           int commandPosition;
        commandPosition=pPath.find_first_of("Mm");
        pPath.erase(0,commandPosition+2);
        pXvalue=stod(pPath.substr(0,pPath.find(",")));
        pPath.erase(0,pPath.find(",")+1);
        pYValue=stod(pPath.substr(0,pPath.find(",")));/* code */
       }
       catch(const std::exception& e)
       {
           //cout << pPath << endl;
       }


    }

    void selectPathPoints(vector<vector<double>>* pAllPoints, string pPoints, double pXMoveValue,double pYMoveValue){
        /*
        Functioning: Extract each point xy from the string of points and store them in the vector pAllPoints.

        Input:
        -pAllPoints
        -pPoints
        -pXMoveValue
        -pYMoveValue

        Output: N/A

        */
        vector<double> vectorXYPoints;
        double xyPoint;
        try
        {
           while(!pPoints.empty()){
            vectorXYPoints.push_back(stoi(pPoints.substr(0, pPoints.find(","))));
            pPoints.erase(0,pPoints.find(",")+1);
            if(pPoints.find(" ")!= string::npos){
                if(stoi(pPoints.substr(0, pPoints.find(" ")))<0){
                    xyPoint=stoi(pPoints.substr(0, pPoints.find(" ")))-pXMoveValue;
                }
                else{
                    xyPoint=stoi(pPoints.substr(0, pPoints.find(" ")));
                }
                vectorXYPoints.push_back(xyPoint);
                pPoints.erase(0,pPoints.find(" ")+1);
            }
            else{
                if(stoi(pPoints.substr(0, pPoints.find(" ")))<0){
                    xyPoint=stoi(pPoints.substr(0, pPoints.find(" ")))-pYMoveValue;
                }
                else{
                    xyPoint=stoi(pPoints.substr(0, pPoints.find(" ")));
                }
                vectorXYPoints.push_back(xyPoint);
                pPoints.erase(0,pPoints.length());
            }
            pAllPoints->push_back(vectorXYPoints);
            vectorXYPoints.clear();
            } /* code */
        }
        catch(const std::exception& e)
        {
            //cout << "jump" << endl;
        }


    }

    vector<vector<double>> selectPathRange(string pPath, double pXMoveValue, double pYMoveValue){
        /*
        Functioning: Extracts the range of xy values from the Cc, Ll, Hh and Vv commands of the path and then calls the selectPathPoints function
         to extract each of those points and store it in the vector of path points.

        Input:
        -pPath
        -pXMoveValue
        -pYMoveValue

        Output:
        -pathPoints

        */
        vector<vector<double>> pathPoints;
        vector<string>pathCommands={"Cc","Ll","Hh","Vv"};
        string tempPath;
        int commandPosition;
        for(int position=0;position<pathCommands.size();position++){
                tempPath=pPath;
                commandPosition=tempPath.find_first_of(pathCommands[position]);
            while(commandPosition!=std::string::npos){
                tempPath.erase(0,commandPosition+2);
                commandPosition=tempPath.find_first_of("ZzCcLlHhVvSsQqTtAa");
                if(pathCommands[position]=="Hh"){
                    selectPathPoints(&pathPoints,tempPath.substr(0,commandPosition).append("0"),pXMoveValue,pYMoveValue);
                }
                else if(pathCommands[position]=="Vv"){
                    selectPathPoints(&pathPoints,"0 "+tempPath.substr(0,commandPosition),pXMoveValue,pYMoveValue);
                }
                else{
                    selectPathPoints(&pathPoints,tempPath.substr(0,commandPosition-1),pXMoveValue,pYMoveValue);
                }
                tempPath.erase(0,commandPosition);
                commandPosition=tempPath.find_first_of(pathCommands[position]);
            }
        }

        return pathPoints;
    }


    void matchPosition(xml_node<>* pNode, vector<string>pColors, vector<vector<double>>pPositions,string pMatchColor,SVG* pSVG){
        /*
        Functioning: Check if in the list of points xy there is any match with the dimensions of the element.
        If so, its respective element is created and stored in the solution vector.

        Input:
        -pNode
        -pColors
        -pPositions
        -pMatchColor
        -pSVG

        Output: N/A

        */
        if(string(pNode->name())=="circle"){
            Circle* newCircle=new Circle(atof(pNode->first_attribute("r")->value()), atof(pNode->first_attribute("cx")->value()),atof(pNode->first_attribute("cy")->value()),
                                        pMatchColor);
            for(int position=0;position<pPositions.size();position++){
                if(newCircle->findMatchPosition(pPositions[position][0],pPositions[position][1])){
                    pSVG->setElement(newCircle);
                    break;
                }
            }
        }
        else if(string(pNode->name())=="rect"){
            Rectangle* newRectangle=new Rectangle(atof(pNode->first_attribute("width")->value()),atof(pNode->first_attribute("x")->value()),
                                         atof(pNode->first_attribute("y")->value()),pMatchColor,atof(pNode->first_attribute("height")->value()));
            for(int position=0;position<pPositions.size();position++){
                if(newRectangle->findMatchPosition(pPositions[position][0],pPositions[position][1])){
                    pSVG->setElement(newRectangle);
                    break;
                }
            }
        }
        else if(string(pNode->name())=="ellipse"){
            Ellipse* newEllipse=new Ellipse(atof(pNode->first_attribute("rx")->value()),atof(pNode->first_attribute("ry")->value()),
                                         atof(pNode->first_attribute("cx")->value()),atof(pNode->first_attribute("cy")->value()),pMatchColor);
            for(int position=0;position<pPositions.size();position++){
                if(newEllipse->findMatchPosition(pPositions[position][0],pPositions[position][1])){
                    pSVG->setElement(newEllipse);
                    break;
                }
            }
        }
        else if(string(pNode->name())=="polyline"){
            vector<vector<double>> points=getPoints(pNode->first_attribute("points")->value());
            Polyline* newPolyline=new Polyline(points,pMatchColor);
            for(int position=0;position<pPositions.size();position++){
                if(newPolyline->findMatchPosition(pPositions[position][0],pPositions[position][1])){
                    pSVG->setElement(newPolyline);
                    break;
                }
            }
        }
        else if(string(pNode->name())=="polygon"){
            vector<vector<double>> points=getPoints(pNode->first_attribute("points")->value());
            Polygon* newPolygon=new Polygon(points,pMatchColor);
            for(int position=0;position<pPositions.size();position++){
                if(newPolygon->findMatchPosition(pPositions[position][0],pPositions[position][1])){
                   pSVG->setElement(newPolygon);
                   break;
                }
            }
        }
        else if(string(pNode->name())=="line"){
            Line* newLine=new Line(atof(pNode->first_attribute("y1")->value()),atof(pNode->first_attribute("x1")->value()),
                                         atof(pNode->first_attribute("x2")->value()),atof(pNode->first_attribute("y2")->value()),pMatchColor);
            for(int position=0;position<pPositions.size();position++){
                if(newLine->findMatchPosition(pPositions[position][0],pPositions[position][1])){
                    pSVG->setElement(newLine);
                    break;
                }
            }
        }
        else if(string(pNode->name())=="path"){
            string pathValue=pNode->first_attribute("d")->value();
            double pathXValue = 0, pathYValue = 0;
            getMoveValues(pathXValue,pathYValue,pathValue);
            Path* newPath=new Path(pathXValue,pathYValue,selectPathRange(pathValue,pathXValue,pathYValue),pMatchColor);
            newPath->setAttributeD(pNode->first_attribute("d")->value());
            for(int position=0;position<pPositions.size();position++){
                if(newPath->findMatchPosition(pPositions[position][0],pPositions[position][1])){
                    pSVG->setElement(newPath);
                    break;
                }
            }
        }
    }

    bool matchColor(string pInputColor, string pElementColor){
        /*
        Functioning: Receives the color of the element and the color to do math with in hexadecimal and then converts them to RGB. After that,
        it starts with color approximation comparison.

        Input:
        -pInputColor
        -pElementColor

        Output:
        -True if there is a match.
        -False if there isn't a match.
        */

        vector<int> inputColor=colorConverterHexToRBG(pInputColor.c_str()),elementColor=colorConverterHexToRBG(pElementColor.c_str());

        if(inputColor[0]==elementColor[0]&&inputColor[1]==elementColor[1]&&inputColor[2]==elementColor[2]){
            return true;
        }
        else if(inputColor[0]>=50&&inputColor[0]<=255&&elementColor[0]>=50&&elementColor[0]<=255&&inputColor[1]>=0&&inputColor[1]<=190&&elementColor[1]>=0&&elementColor[1]<=190&&
           inputColor[2]>=0&&inputColor[2]<=190&&elementColor[2]>=0&&elementColor[2]<=190){
            return true;
        }
        else if(inputColor[0]>=170&&inputColor[0]<=255&&elementColor[0]>=170&&elementColor[0]<=255&&inputColor[1]>=50&&inputColor[1]<=190&&
                elementColor[1]>=50&&elementColor[1]<=190&&inputColor[2]>=0&&inputColor[2]<=80&&elementColor[2]>=0&&elementColor[2]<=80){
            return true;
        }
        else if(inputColor[0]>=170&&inputColor[0]<=255&&elementColor[0]>=170&&elementColor[0]<=255&&inputColor[1]>=160&&inputColor[1]<=255&&
                elementColor[1]>=160&&elementColor[1]<=255&&inputColor[2]>=0&&inputColor[2]<=190&&elementColor[2]>=0&&elementColor[2]<=190){
            return true;
        }
        else if(inputColor[0]>=0&&inputColor[0]<=200&&elementColor[0]>=0&&elementColor[0]<=200&&inputColor[1]>=170&&inputColor[1]<=255&&elementColor[1]>=170&&
                elementColor[1]<=255&&inputColor[2]>=0&&inputColor[2]<=190&&elementColor[2]>=0&&elementColor[2]<=190){
            return true;
        }
        else if(inputColor[0]>=0&&inputColor[0]<=200&&elementColor[0]>=0&&elementColor[0]<=200&&inputColor[1]>=0&&inputColor[1]<=250&&
                elementColor[1]>=0&&elementColor[1]<=250&&inputColor[2]>=140&&inputColor[2]<=255&&elementColor[2]>=140&&elementColor[2]<=255||
                inputColor[0]>=150&&inputColor[0]<=255&&elementColor[0]>=150&&elementColor[0]<=255&&inputColor[1]>=0&&inputColor[1]<=90&&
                elementColor[1]>=0&&elementColor[1]<=90&&inputColor[2]>=90&&inputColor[2]<=255&&elementColor[2]>=90&&elementColor[2]<=255){
            return true;
        }
        else if(inputColor[0]>=80&&inputColor[0]<=150&&elementColor[0]>=80&&elementColor[0]<=150&&inputColor[1]>=25&&inputColor[1]<=50&&
                elementColor[1]>=25&&elementColor[1]<=50&&inputColor[2]==0&&elementColor[2]==0){
            return true;
        }
        else if(inputColor[0]>=0&&inputColor[0]<=230&&elementColor[0]>=0&&elementColor[0]<=230&&inputColor[1]>=0&&inputColor[1]<=230&&
                elementColor[1]>=0&&elementColor[1]<=230&&inputColor[2]>=0&&inputColor[2]<=230&&elementColor[2]>=0&&elementColor[2]<=230
                &&inputColor[0]==elementColor[0]&&inputColor[1]==elementColor[1]&&inputColor[2]==elementColor[2]){
            return true;
        }
        else if(inputColor[0]>=230&&inputColor[0]<=250&&elementColor[0]>=230&&elementColor[0]<=250&&inputColor[1]>=230&&inputColor[1]<=250&&
                elementColor[1]>=230&&elementColor[1]<=250&&inputColor[2]>=230&&inputColor[2]<=250&&elementColor[2]>=230&&elementColor[2]<=250
                &&inputColor[0]==elementColor[0]&&inputColor[1]==elementColor[1]&&inputColor[2]==elementColor[2]){
            return true;
        }
        else{
            return false;
        }

    }

    void startSelection(xml_node<>* pNode, vector<string> pColors, vector<vector<double>>pPositions,SVG *pSVG){
        /*
        Functioning: It goes through the nodes of the svg and verifies that there is a match of an element by approach color and xy positions.

        Input:
        -pNode
        -pColors = Vector with focus colors
        -pPositions = Vector of points to match the position.
        -pSVG

        Output: N/A

        */
        vector<int> inputColorConverted, elementColorConverted;
        for (pNode = pNode->first_node(); pNode != NULL; pNode = pNode->next_sibling()){
            if (pNode->type() == node_element){
                    for(int position=0;position<pColors.size();position++){
                        if(pNode->first_attribute("fill")){
                            if(matchColor(pColors[position],pNode->first_attribute("fill")->value())){
                                matchPosition(pNode,pColors,pPositions,pColors[position],pSVG);
                            }
                        }
                        else if(pNode->first_attribute("stroke")){
                            if(matchColor(pColors[position],pNode->first_attribute("fill")->value())){
                                matchPosition(pNode,pColors,pPositions,pColors[position],pSVG);
                            }
                        }
                        else if(pNode->first_attribute("style")){
                            string styleValue=pNode->first_attribute("style")->value();
                            if(styleValue.find_first_of("#")!=string::npos){
                                string hexColor=styleValue.substr(styleValue.find_first_of("#"),styleValue.find_first_of(";")-styleValue.find_first_of("#"));
                                if(matchColor(pColors[position],hexColor)){
                                    matchPosition(pNode,pColors,pPositions,pColors[position],pSVG);
                                }
                            }
                        }
                }
                startSelection(pNode,pColors,pPositions,pSVG);
            }
      }

    }
};
#endif
