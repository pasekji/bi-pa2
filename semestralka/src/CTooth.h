#ifndef TOOTH_H
#define TOOTH_H

#include "CMisc.h"

/**
 * This class represents tooth as ingame item.
 * CTooth inherits from CMisc.
 * */
class CTooth : public CMisc
{
    public:
        /**
         * CTooth default constructor 
         * */
        CTooth() = default;

        /**
         * CTooth default destructor 
         * */
        virtual ~CTooth() = default;

        /**
         * CTooth label getter, 
         * used to get label of this class, 
         * return std::string value.
         * */
        std::string getLabel() const override;
};

#endif