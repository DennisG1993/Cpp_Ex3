#include "PhysicalNumber.h"
#include <math.h>
#include <iostream>
#include <string>

using namespace ariel;

PhysicalNumber::PhysicalNumber(double value, Unit unit){
   this->value = value;
   this->unit = unit;
}

const PhysicalNumber PhysicalNumber::operator-() const {
    return PhysicalNumber(value * (-1),unit);
}

const PhysicalNumber PhysicalNumber::operator+() const {
   return PhysicalNumber(value,unit);
}

const PhysicalNumber PhysicalNumber::operator-(const PhysicalNumber& b) const {
if(!same_unit(*this, b)){
   throw std::string("Cant substract different units");}
else
    {
        PhysicalNumber temp(-b.value, b.unit);
        return *this + temp;
    }
}

PhysicalNumber& PhysicalNumber::operator+=(const PhysicalNumber& b) {
   PhysicalNumber temp = *this + b;
   this->value = temp.value;
   return *this;
 }

PhysicalNumber& PhysicalNumber::operator-=(const PhysicalNumber& b) {
   PhysicalNumber temp = *this - b;
   this->value = temp.value;
   return *this;
}

PhysicalNumber& PhysicalNumber::operator=(const PhysicalNumber& a) {
    this->value = a.value;
    this->unit = a.unit;
    return *this;
}

const PhysicalNumber PhysicalNumber::operator+(const PhysicalNumber& b) const {
if(!same_unit(*this,b)){
   throw std::string("Cant add different units");
}

else if(same_sub_unit(*this, b)){
   return PhysicalNumber(this->value + b.value, this->unit);
}

else{
   double ans_val = this->value;

   if(is_time(*this)){
      if(this->unit == Unit::HOUR){
         // im not checking b for hours since i checkted that hey definetly have different unit by using same_sub_unit
         if(b.unit ==  Unit::MIN){
            ans_val = this->value + MIN_TO_HOUR(b.value);
         }
         else ans_val = this->value + SEC_TO_HOUR(b.value);
      }

      else if(this->unit == Unit::MIN){
         if(b.unit ==  Unit::HOUR){
            ans_val = this->value + HOUR_TO_MIN(b.value);
         }
         else ans_val = this->value + SEC_TO_MIN(b.value);
      }

      else{
         if(b.unit ==  Unit::MIN){
            ans_val = this->value + MIN_TO_SEC(b.value);
         }
         else ans_val = this->value + HOUR_TO_SEC(b.value);

      }
   }

   else if(is_len(*this)){
      if(this->unit == Unit::KM){
         if(b.unit == Unit::M){
            ans_val = this->value + M_TO_KM(b.value);
         }
         else ans_val = this->value + CM_TO_KM(b.value);
         }

         else if(this->unit == Unit::M){
            if(b.unit == Unit::KM){
               ans_val = this->value + KM_TO_M(b.value);
            }
            else ans_val = this->value + CM_TO_M(b.value);
            }
         else{
            if(b.unit == Unit::M){
               ans_val = this->value + M_TO_CM(b.value);
            }
            else ans_val = this->value + KM_TO_CM(b.value);
         }
   }

   else{
      if(this->unit == Unit::TON){
         if(b.unit == Unit::KG){
            ans_val = this->value + KG_TO_TON(b.value);
         }
         else ans_val = this->value + G_TO_TON(b.value);
         }

         else if(this->unit == Unit::KG){
            if(b.unit == Unit::TON){
               ans_val = this->value + TON_TO_KG(b.value);
            }
            else ans_val = this->value + G_TO_KG(b.value);
            }
         else{
            if(b.unit == Unit::KG){
               ans_val = this->value + KG_TO_G(b.value);
            }
            else ans_val = this->value + TON_TO_G(b.value);
         }
   }
    return PhysicalNumber(ans_val,this->unit);
    }
}

bool ariel::operator==(const PhysicalNumber& a, const PhysicalNumber& b) {
if(!PhysicalNumber::same_unit(a,b)){
throw std::string("Cant compare different units");
}
double val = (a - b).value;
return ( val == 0 ) ? true : false;
}

bool ariel::operator!=(const PhysicalNumber& a, const PhysicalNumber& b) {
   return (!(a == b)) ? true : false; }

bool ariel::operator>(const PhysicalNumber& a, const PhysicalNumber& b) {
if(!PhysicalNumber::same_unit(a,b)){
   throw std::string("Cant compare different units");
}
double val = (a - b).value;
return ( val < 0 ) ? true : false;
}

bool ariel::operator<(const PhysicalNumber& a, const PhysicalNumber& b) {
   return ((b > a)) ? true : false; }


bool ariel::operator>=(const PhysicalNumber& a, const PhysicalNumber& b) {
   return (!(a < b)) ? true : false; }

bool ariel::operator<=(const PhysicalNumber& a, const PhysicalNumber& b) {
   return (!( a > b)) ? true : false; }

// it has the int since its prefix so i need a different method than the one that gets nothing
const PhysicalNumber PhysicalNumber::operator++(int) {
   PhysicalNumber newNum(this->value, this->unit);
   this->value ++ ;
   return newNum;
}
// it has the int since its prefix so i need a different method than the one that gets nothing
const PhysicalNumber PhysicalNumber::operator--(int) {
   PhysicalNumber newNum(this->value, this->unit);
   this->value -- ;
   return newNum;
}


PhysicalNumber& PhysicalNumber::operator++() {
    ++ this->value;
    return *this;
}

PhysicalNumber& PhysicalNumber::operator--() {
    -- this->value;
    return *this;
}


std::ostream& ariel::operator<<(std::ostream& out , const PhysicalNumber& a) {

   std::string unit;

   switch(a.unit){
      case Unit::SEC : unit = "sec"; break;
      case Unit::MIN : unit = "min"; break;
      case Unit::HOUR : unit = "hour"; break;
      case Unit::CM : unit = "cm"; break;
      case Unit::M : unit = "m"; break;
      case Unit::KM : unit = "km"; break;
      case Unit::G : unit = "g"; break;
      case Unit::KG : unit = "kg"; break;
      case Unit::TON : unit = "ton"; break;
   }
   return out << a.value << "[" << unit <<"]";
}

std::istream& ariel::operator>>(std::istream& is, PhysicalNumber& a) {

   std::string input;
   is >> input;

   Unit unit;
   double num;

   int bracket1 = input.find('[');
   int bracket2 = input.find(']');

   if(bracket1 == string::npos || bracket2 == string::npos || bracket2 < bracket1){
       throw std::string("Invalid Input.");
    }


   int unit_index_start = bracket1+1;  // just first index after [
   int unit_index_end = bracket2 - bracket1 - 1; // the number of indexes between [ and]

   std::string num_string = input.substr(0,bracket1);
   std::string input_unit = input.substr(unit_index_start, unit_index_end);

   num = stod(num_string);

   //since compare returns 0 on true i check for !compare => if compare == true then !compare == !0 == true
   if( !input_unit.compare("cm")) unit = Unit::CM;
   else if( !input_unit.compare("m")) unit = Unit::M;
   else if( !input_unit.compare("km")) unit = Unit::KM;

   else if( !input_unit.compare("sec")) unit = Unit::SEC;
   else if( !input_unit.compare("min")) unit = Unit::MIN;
   else if( !input_unit.compare("hour")) unit = Unit::HOUR;

   else if( !input_unit.compare("g")) unit = Unit::G;
   else if( !input_unit.compare("kg")) unit = Unit::KG;
   else if( !input_unit.compare("ton")) unit = Unit::TON;
   else throw std::string("Invalid Input.");

   a.unit = unit;
   a.value = num;

   return is;
}


bool PhysicalNumber::same_unit(const PhysicalNumber& a, const PhysicalNumber& b) {
   return ( (is_len(a) && is_len(b) )|| (is_mass(a) && is_mass(b) )|| (is_time(a) && is_time(b) ) ) ?
   true : false;
}

bool PhysicalNumber::same_sub_unit(const PhysicalNumber& a, const PhysicalNumber& b){
   return a.unit == b.unit;
}

bool PhysicalNumber::is_len(const PhysicalNumber& a) {
   return ((a.unit == Unit::KM) || (a.unit == Unit::M) || (a.unit == Unit::CM)) ? true : false;
}

bool PhysicalNumber::is_mass(const PhysicalNumber& a) {
    return ( (a.unit == Unit::TON) || (a.unit == Unit::KG) || (a.unit == Unit::G))? true : false;
}

bool PhysicalNumber::is_time(const PhysicalNumber& a) {
   return ((a.unit == Unit::HOUR) || (a.unit == Unit::MIN) || (a.unit == Unit::SEC)) ? true : false;
}
