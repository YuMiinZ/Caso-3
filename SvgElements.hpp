#ifndef __SVG_PATHS_HEADER__
#define __SVG_PATHS_HEADER__

#include <math.h>
#include <vector>
#include <cstring>
class Element{
    protected:
        double coordX, coordY, coordX2, coordY2, side, area, finalCoordX, finalCoordY, hypotenuse, displacement, auxCoordX, auxCoordY;
        bool rect,generateElement;
        vector<vector<int>> movements; // { {x,y}, {}, {}, {} }
        vector<vector<int>> movements2;
        string color, attribute;
        int fileName;
    public:
        Element(){};
        Element(double pNewSide){side=pNewSide;};
        Element(double pNewXValue, double pNewYValue){coordX=pNewXValue;coordY=pNewYValue;};
        void setAttribute(string pNewAttribute){attribute = pNewAttribute;};
        void setXCoord(double pNewXValue){coordX=pNewXValue;};
        void setYCoord(double pNewYValue){coordY=pNewYValue;};
        void setAuxXCoord(double pNewAuxXValue){auxCoordX=pNewAuxXValue;};
        void setAuxYCoord(double pNewAuxYValue){auxCoordY=pNewAuxYValue;};
        void setFinalXCoord(double pNewfinalCoordX){finalCoordX = pNewfinalCoordX;};
        void setFinalYCoord(double pNewfinalCoordY){finalCoordY = pNewfinalCoordY;};
        void setHypotenuse(double pNewHypotenuse){hypotenuse = pNewHypotenuse;};
        void setDisplacement(double pNewDisplacement){displacement = pNewDisplacement;};
        void setSide(double pNewSide){side=pNewSide;};
        void setRect(bool pNewRect){rect = pNewRect;};
        virtual void findMatchPosition(){};
        void setColor(string pNewColor){color=pNewColor;};
        double getXCoord(){return coordX;};
        double getYCoord(){return coordY;};
        double getAuxXCoord(){return auxCoordX;};
        double getAuxYCoord(){return auxCoordY;};
        double getSide(){return side;};
        double getArea(){return area;};
        string getColor(){return color;};
        double getDisplacement(){return displacement;};
        double getFinalXCoord(){return finalCoordX;};
        double getFinalYCoord(){return finalCoordY;};
        double getHypotenuse(){return hypotenuse;};
        string getAttribute(){return attribute;};
        vector<vector<int>> getMovements(){return movements;};
        bool isRect(){return rect;};
        void addMovement(int pXValue, int pYValue){
            vector<int> point = {pXValue,pYValue}; movements.push_back(point);
        };

        void setLineEndXValue(double pNewEndXValue){coordX2=pNewEndXValue;};
        void setLineEndYValue(double pNewEndYValue){coordY2=pNewEndYValue;};
        double getLineEndXValue(){return coordX2;};
        double getLineEndYValue(){return coordY2;};
        vector<vector<int>> getMovements2(){return movements2;};
        void addMovement2(int pNewX2, int pNewY2){vector<int> point = {pNewX2,pNewY2}; movements2.push_back(point);}
        void setGenerateElement(bool state){generateElement=state;};
        bool getGenerateElement(){return generateElement;};
        void setNumberFileName(int pFileName){fileName=pFileName;};
        int getNumberFileName(){return fileName;};
        virtual void createSVGAttribute(xml_document<> *myDoc){};
};

class Circle:public Element{
    private:
    public:
        Circle(){ Element::attribute = "circle";};
        Circle(double pNewRadio, double pNewXCoord, double pNewYCoord, string pNewColor){Element::setXCoord(pNewXCoord);Element::setYCoord(pNewYCoord);
        Element::setSide(pNewRadio);Element::setColor(pNewColor); Element::attribute = "circle";};
        Circle(double pNewRadio){Element::setSide(pNewRadio); Element::attribute = "circle";};
        bool findMatchPosition(double pXValue, double pYValue);

        void createSVGAttribute(xml_document<> *myDoc){
            xml_node<> *newNode = myDoc->allocate_node(node_element, attribute.c_str());


            string Scx = to_string(coordX);
            string Scy = to_string(coordY);
            string Sside = to_string(coordY);

            char* cstrX = new char[to_string(coordX).size() + 1];  // Create char buffer to store string copy
            strcpy (cstrX, to_string(coordX).c_str());
            xml_attribute<> *cx = myDoc->allocate_attribute("cx", cstrX);
            newNode->append_attribute(cx);

            char* cstrY = new char[to_string(coordY).size() + 1];  // Create char buffer to store string copy
            strcpy (cstrY, to_string(coordY).c_str());
            xml_attribute<> *cy = myDoc->allocate_attribute("cy", cstrY);
            newNode->append_attribute(cy);

            char* cstrR = new char[to_string(side).size() + 1];  // Create char buffer to store string copy
            strcpy (cstrR, to_string(side).c_str());
            xml_attribute<> *r = myDoc->allocate_attribute("r", cstrR);
            newNode->append_attribute(r);

            xml_attribute<> *opacity = myDoc->allocate_attribute("opacity", "0.5");
            newNode->append_attribute(opacity);


            xml_attribute<> *fill = myDoc->allocate_attribute("fill", color.c_str());
            newNode->append_attribute(fill);

            myDoc->first_node()->append_node(newNode);
        }

};

 bool Circle::findMatchPosition(double pXValue,double pYValue){

    if(pow((pXValue-(Element::coordX)),2.0)+pow((pYValue-(Element::coordY)),2.0)<=pow(Element::getSide(),2.0)){
        return true;
     }
     else{
        return false;
     }
}


class Rectangle:public Element{
    private:
        int width, height;
    public:
        Rectangle(){Element::attribute = "rect";};
        Rectangle(double pNewWidth){width=pNewWidth; Element::attribute = "rect";};
        Rectangle(double pNewWidth, double pNewXCoord, double pNewYCoord, string pNewColor, double pNewHeight){width=pNewWidth;Element::setXCoord(pNewXCoord);
        Element::setYCoord(pNewYCoord);Element::setSide(pNewHeight);Element::setColor(pNewColor); Element::attribute = "rect";};
        void setWidth(double pNewWidth){width=pNewWidth;};
        void setHeight(double pNewHeight){height=pNewHeight;};
        int getWidth(){return width;};
        int getHeight(){return height;};
        bool findMatchPosition(double pXValue, double pYValue);

        void createSVGAttribute(xml_document<> *myDoc){
            xml_node<> *newNode = myDoc->allocate_node(node_element, attribute.c_str());
            myDoc->first_node()->append_node(newNode);
            xml_attribute<> *x = myDoc->allocate_attribute("x", to_string(coordX).c_str());
            newNode->append_attribute(x);
            xml_attribute<> *y = myDoc->allocate_attribute("y", to_string(coordY).c_str());
            newNode->append_attribute(y);
            xml_attribute<> *attrWidth = myDoc->allocate_attribute("width", to_string(width).c_str());
            newNode->append_attribute(attrWidth);
            xml_attribute<> *attrHeight = myDoc->allocate_attribute("height", to_string(height).c_str());
            newNode->append_attribute(attrHeight);
            xml_attribute<> *fill = myDoc->allocate_attribute("fill", color.c_str());
            newNode->append_attribute(fill);
        }

};

bool Rectangle::findMatchPosition(double pXValue, double pYValue){
    double maxWidth=Element::getXCoord()+width, maxLength=Element::getYCoord()+Element::getSide();
    if((pXValue<=maxWidth&&(pXValue>=Element::getXCoord()))&&(pYValue<=maxLength&&(pYValue>=Element::getYCoord()))){
        return true;
    }
    else{
        return false;
    }
}

class Ellipse:public Element{
    private:
        double yRadio;
    public:
        Ellipse(){Element::attribute = "ellipse";};//FALTA CAMBIAR LOS XRADIO POR SETSIDE
        Ellipse(double pNewXRadio,double pNewYRadio, double pNewXCoord, double pNewYCoord, string pNewColor){Element::setSide(pNewXRadio);yRadio=pNewYRadio;
        Element::setColor(pNewColor);Element::setXCoord(pNewXCoord);Element::setYCoord(pNewYCoord); Element::attribute = "ellipse";};
        void setXRadio(double pNewXRadio){Element::setSide(pNewXRadio);};
        void setYRadio(double pNewYRadio){yRadio=pNewYRadio;};
        double getXRadio(){return Element::getSide();};
        double getYRadio(){return yRadio;};
        bool findMatchPosition(double pXValue, double pYValue);

        void createSVGAttribute(xml_document<> *myDoc){
            xml_node<> *newNode = myDoc->allocate_node(node_element, attribute.c_str());
            xml_node<> *parentNode = myDoc->first_node();

            char* cstrX = new char[to_string(coordX).size() + 1];  // Create char buffer to store string copy
            strcpy (cstrX, to_string(coordX).c_str());
            xml_attribute<> *cx = myDoc->allocate_attribute("cx", cstrX);
            newNode->append_attribute(cx);

            char* cstrY = new char[to_string(coordY).size() + 1];  // Create char buffer to store string copy
            strcpy (cstrY, to_string(coordY).c_str());
            xml_attribute<> *cy = myDoc->allocate_attribute("cy", cstrY);
            newNode->append_attribute(cy);

            char* cstrR = new char[to_string(side).size() + 1];  // Create char buffer to store string copy
            strcpy (cstrR, to_string(side).c_str());
            xml_attribute<> *rx = myDoc->allocate_attribute("rx", cstrR);
            newNode->append_attribute(rx);

            char* cstrRY = new char[to_string(yRadio).size() + 1];  // Create char buffer to store string copy
            strcpy (cstrRY, to_string(yRadio).c_str());
            xml_attribute<> *ry = myDoc->allocate_attribute("ry", cstrRY);
            newNode->append_attribute(ry);

            char* cstrColor = new char[color.size() + 1];  // Create char buffer to store string copy
            strcpy (cstrColor, color.c_str());
            xml_attribute<> *fill = myDoc->allocate_attribute("fill", cstrColor);
            newNode->append_attribute(fill);
        }
};

bool Ellipse::findMatchPosition(double pXValue, double pYValue){
    if((pXValue>=(Element::getXCoord()-Element::getSide()))&&(pXValue<=(Element::getXCoord()+Element::getSide()))&&
       (pYValue>=(Element::getYCoord()-yRadio))&&(pYValue<=(Element::getYCoord()+yRadio))){
        return true;
       }
    else{
        return false;
    }
}

class Polyline:public Element{
    private:
        vector<vector<double>> xyCoords;
    public:
        Polyline(){Element::attribute = "polyline";};
        Polyline(vector<vector<double>> pNewXYCoords, string pColor){xyCoords=pNewXYCoords; Element::setColor(pColor); Element::attribute = "polyline";};
        Polyline(vector<vector<double>> pNewXYCoords){xyCoords=pNewXYCoords;Element::attribute = "polyline";};
        void setXYCoord(vector<double> pNewxyCoords){xyCoords.push_back(pNewxyCoords);};
        vector<vector<double>> getXYCoord(){return xyCoords;};
        bool findMatchPosition(double pXValue, double pYValue);

        void createSVGAttribute(xml_attribute<> *newAttr, xml_document<> *myDoc){

        }

};

bool Polyline::findMatchPosition(double pXValue, double pYValue){
    double maxYValue=xyCoords[0][1], maxXValue=xyCoords[0][0], minYValue=xyCoords[0][1], minXValue=xyCoords[0][0];

    for(int posicion=1;posicion<xyCoords.size();posicion++){
        if((xyCoords[posicion][1]>maxYValue)){
            maxYValue=xyCoords[posicion][1];
        }
        if((xyCoords[posicion][1]<minYValue)){
            minYValue=xyCoords[posicion][1];
        }
        if((xyCoords[posicion][0]>minXValue)){
            maxXValue=xyCoords[posicion][0];
        }
        if((xyCoords[posicion][0]<minXValue)){
            minXValue=xyCoords[posicion][0];
        }
    }
    if((pXValue>=minXValue)&&(pXValue<=maxXValue)&&(pYValue>=minYValue)&&(pYValue<=maxYValue)){
        return true;
    }
    else{
        return false;
    }

}

class Polygon:public Element{
    private:
        vector<vector<double>> xyCoords;
    public:
        Polygon(){Element::attribute = "polygon";};
        Polygon(vector<vector<double>> pNewCoords,string pColor){xyCoords=pNewCoords; Element::setColor(pColor); Element::attribute = "polygon";};
        Polygon(vector<vector<double>> pNewCoords){xyCoords=pNewCoords;Element::attribute = "polygon";};
        void setXYCoord(vector<double> pNewxyCoords){xyCoords.push_back(pNewxyCoords);};
        vector<vector<double>> getXYCoord(){return xyCoords;};
        bool findMatchPosition(double pXValue, double pYValue);

        void createSVGAttribute(xml_attribute<> *newAttr, xml_document<> *myDoc){

        }

};

bool Polygon::findMatchPosition(double pXValue, double pYValue){
    double maxYValue=xyCoords[0][1], maxXValue=xyCoords[0][0], minYValue=xyCoords[0][1], minXValue=xyCoords[0][0];

    for(int posicion=1;posicion<xyCoords.size();posicion++){
        if((xyCoords[posicion][1]>maxYValue)){
            maxYValue=xyCoords[posicion][1];
        }
        if((xyCoords[posicion][1]<minYValue)){
            minYValue=xyCoords[posicion][1];
        }
        if((xyCoords[posicion][0]>minXValue)){
            maxXValue=xyCoords[posicion][0];
        }
        if((xyCoords[posicion][0]<minXValue)){
            minXValue=xyCoords[posicion][0];
        }
    }
    if((pXValue>=minXValue)&&(pXValue<=maxXValue)&&(pYValue>=minYValue)&&(pYValue<=maxYValue)){
        return true;
    }
    else{
        return false;
    }
}

class Line:public Element{
    private:
        double endXValue, endYValue;
    public:
        Line(){Element::attribute = "line";};
        Line(double newYCoord, double newXCoord, double newEndXValue,double newEndYValue,string pColor){Element::coordX=newXCoord; Element::coordY=newYCoord;
        endXValue=newEndXValue;endYValue=newEndYValue; Element::setColor(pColor); Element::attribute = "line";};
        Line(double pNewYCoord, double pNewXCoord, double pNewEndXValue,double pNewEndYValue){Element::coordX=pNewYCoord; Element::coordY=pNewXCoord;
        endXValue=pNewEndXValue;endYValue=pNewEndYValue; Element::attribute = "line";};
        bool findMatchPosition(double pXValue, double pYValue);
        /*string getString(){return "Rectangle: X Value = "+to_string(Element::coordX)+" Y Value = "+to_string(Element::coordY)
        +" Horizontal Radio = "+to_string(xRadio)+" Vertical Radio = "+to_string(yRadio)+" Area = "+to_string(Element::getArea())+"\n";};*/

        void createSVGAttribute(xml_document<> *myDoc){
            xml_node<> *newNode = myDoc->allocate_node(node_element, attribute.c_str());
            myDoc->first_node()->append_node(newNode);

            char* cstrx1 = new char[to_string(coordX).size() + 1];  // Create char buffer to store string copy
            strcpy (cstrx1, to_string(coordX).c_str());
            xml_attribute<> *x1 = myDoc->allocate_attribute("x1", cstrx1);
            newNode->append_attribute(x1);

            char* cstry1 = new char[to_string(coordY).size() + 1];  // Create char buffer to store string copy
            strcpy (cstry1, to_string(coordY).c_str());
            xml_attribute<> *y1 = myDoc->allocate_attribute("y1", cstry1);
            newNode->append_attribute(y1);

            char* cstrx2 = new char[to_string(endXValue).size() + 1];  // Create char buffer to store string copy
            strcpy (cstrx2, to_string(endXValue).c_str());
            xml_attribute<> *x2 = myDoc->allocate_attribute("x2", cstrx2);
            newNode->append_attribute(x2);

            char* cstry2 = new char[to_string(endYValue).size() + 1];  // Create char buffer to store string copy
            strcpy (cstry2, to_string(endYValue).c_str());
            xml_attribute<> *y2 = myDoc->allocate_attribute("y2", cstry2);
            newNode->append_attribute(y2);

            char* cstrcolor = new char[color.size() + 1];  // Create char buffer to store string copy
            strcpy (cstrcolor, color.c_str());
            xml_attribute<> *fill = myDoc->allocate_attribute("fill", cstrcolor);
            newNode->append_attribute(fill);
        }

};

bool Line::findMatchPosition(double pXValue, double pYValue){
    if((pXValue>=Element::getXCoord()&&pXValue<=endXValue)&&(pYValue>=Element::getYCoord()&&pYValue<=(endYValue-Element::getXCoord()))){
        return true;
    }
    else{
        return false;
    }
}

class Path:public Element{
    private:
        int degrees;
        string attributeD;
        vector<vector<double>>curvePositions;
    public:
        Path(){Element::attribute = "path";};
        Path(double pNewXMove, double pNewYMove, vector<vector<double>>pNewCurvePositions,string pColor){Element::setXCoord(pNewXMove);Element::setYCoord(pNewYMove);
        curvePositions=pNewCurvePositions; Element::attribute = "path"; Element::color=pColor;};
        void setCurvePositions(vector<double> pNewCurvePosition){curvePositions.push_back(pNewCurvePosition);};
        void setAttributeD(string newAttributeD){attributeD = newAttributeD;};
        void setDegrees(int pDegrees){degrees = pDegrees;};
        vector<vector<double>> getCurvePositions(){return curvePositions;};
        string getAttributeD(){return attributeD;};
        int getDegrees(){return degrees;};
        bool findMatchPosition(double pXValue, double pYValue);

        xml_node<>* findGNode(xml_node<>* pNode){
            xml_node<>* currentNode = pNode;
            while(true){
                if (currentNode->next_sibling() == NULL){
                    if (currentNode->first_node()->name() == (string)"path"){
                        //cout << "fin" << endl;
                        return currentNode;
                    }
                    else{
                        //cout << "next child" << endl;
                        currentNode = currentNode->first_node();
                    }
                }
                else{
                    //cout << "next sibling" << endl;
                    currentNode = currentNode->next_sibling();
                }
            }
        }

        string getTransformCoords(){
            int currentDegrees = degrees;
            string str = "translate(";
            // if(currentDegrees <= 90){ //I cuadrante
            // cout << "90 degrees " << endl;
            //     str = str + to_string(coordX - this->getAuxXCoord()) + ", " + to_string(this->getAuxYCoord() - coordY);
            // }
            // else if (currentDegrees > 90 && currentDegrees <= 180){ //II cuadrante
            // cout << "180 degrees" << endl;
            //     str = str + to_string(coordX - this->getAuxXCoord()) + ", " + to_string(this->getAuxYCoord() - coordY);
            // }
            // else if (currentDegrees > 180 && currentDegrees <= 270){ //III cuadrante
            // cout << "270 degrees" << endl;
            //     str = str + to_string(coordX - this->getAuxXCoord()) + ", " + to_string(this->getAuxYCoord() - coordY);
            // }
            // else{ //IV cuadrante
            // cout << "360 degrees" << endl;
            //     str = str + to_string(coordX - this->getAuxXCoord()) + ", " + to_string(this->getAuxYCoord() - coordY);
            // }
            str = str + to_string(coordX - this->getAuxXCoord()) + ", " + to_string(this->getAuxYCoord() - coordY);
            return str + ")";
        }

        void createSVGAttribute(xml_document<> *myDoc){

            string auxAttributeD = attributeD;
            int mIndex = attributeD.find_first_of('m');
            if (mIndex == -1 ){mIndex = attributeD.find_first_of('M');}
            int separatorIndex = attributeD.find_first_of(',');
            int finalIndex = attributeD.find_first_not_of(" m1234567890.,") -1;

            double newXValue = Element::coordX;
            double newYValue = Element::coordY;

            // double newXValue = Element::auxCoordX;
            // double newYValue = Element::auxCoordY;

            string newX = to_string(newXValue);
            newX.erase( newX.find_last_not_of('0') + 1, std::string::npos );
            newX.erase( newX.find_last_not_of('.') + 1, std::string::npos );
            string newY = to_string(newYValue);
            newY.erase( newY.find_last_not_of('0') + 1, std::string::npos );
            newY.erase( newY.find_last_not_of('.') + 1, std::string::npos );

            auxAttributeD.replace(separatorIndex+1, finalIndex-1-separatorIndex, newY);
            auxAttributeD.replace(mIndex + 1, separatorIndex-1, newX);

            xml_node<> *newNode = myDoc->allocate_node(node_element, attribute.c_str());

            char* cstr = new char[attributeD.size() + 1];  // Create char buffer to store string copy
            strcpy (cstr, attributeD.c_str());
            xml_attribute<> *d = myDoc->allocate_attribute("d", cstr);
            newNode->append_attribute(d);

            char* cstrColor = new char[color.size() + 1];  // Create char buffer to store string copy
            strcpy (cstrColor, color.c_str());
            xml_attribute<> *fill = myDoc->allocate_attribute("fill", cstrColor);
            newNode->append_attribute(fill);

            char* cstrTransform = new char[getTransformCoords().size() + 1];  // Create char buffer to store string copy
            strcpy (cstrTransform, getTransformCoords().c_str());
            xml_attribute<> *transform = myDoc->allocate_attribute("transform", cstrTransform);
            newNode->append_attribute(transform);

            xml_node<>* nodeG = findGNode(myDoc->first_node());
            nodeG->append_node(newNode);

        }
};

bool Path::findMatchPosition(double pXValue, double pYValue){
    // cout << "entrando a fund match..." << endl;
    // cout << "size: " << curvePositions.size() << endl;
    if(curvePositions.size() == 0){
        return false;
    }
    //double maxYValue=curvePositions[0][1], maxXValue=curvePositions[0][0], minYValue=Element::getYCoord(), minXValue=Element::getXCoord();
    double maxYValue= this->getYCoord(), maxXValue=this->getXCoord(), minYValue=this->getYCoord(), minXValue=this->getXCoord();
    for(int posicion=1;posicion<curvePositions.size();posicion++){
        maxYValue=((curvePositions[posicion][1]>maxYValue)?curvePositions[posicion][1]:maxYValue);
        minYValue=((curvePositions[posicion][1]<minYValue)?curvePositions[posicion][1]:minYValue);
        maxXValue=((curvePositions[posicion][0]>maxXValue)?curvePositions[posicion][0]:maxXValue);
        minXValue=((curvePositions[posicion][0]<minXValue)?curvePositions[posicion][0]:minXValue);

        //cout << curvePositions[posicion][0] << " // " << curvePositions[posicion][1] << endl;
    }
    if((pXValue>=minXValue)&&(pXValue<=maxXValue)&&(pYValue>=minYValue)&&(pYValue<=maxYValue)){
        return true;
    }
    else{
        return false;
    }


}

class SVG{
    private:
        double height, width;
        int frames, degrees;
        string filename;
        vector<Element*>selectedElements;
        xml_document<> *document;
    public:
        SVG(){};
        void setHeight(double pNewHeight){height=pNewHeight;};
        void setWidth(double pNewWidth){width=pNewWidth;};
        void setVectorElements(vector<Element*> pVectorElements){selectedElements=pVectorElements;};
        void setElement(Element* pElement){selectedElements.push_back(pElement);};
        void setFrames(int pNewFrames){frames = pNewFrames;};
        void setDegrees(int pNewDegrees){degrees = pNewDegrees;};
        void setDoc(xml_document<> *pNewDocument){document = pNewDocument;};
        void setFileName(string pNewFileName){filename = pNewFileName;}
        double getHeight(){return height;};
        double getWidth(){return width;};
        int getFrames(){return frames;};
        int getDegrees(){return degrees;};
        xml_document<>* getDoc(){return document;};
        vector<Element*> getVectorElements(){return selectedElements;};
        string getFileName(){return filename;}

};

#endif
