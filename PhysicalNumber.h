#ifndef PHYSICAL_NUMBER_H
#define PHYSICAL_NUMBER_H

#include "Unit.h"
#include <iostream>

using namespace std;

namespace ariel {

   class PhysicalNumber{

   	double value;
   	Unit unit;

   public:
   		PhysicalNumber(double, Unit);

   		const PhysicalNumber operator-() const;
   		const PhysicalNumber operator+() const;
   		const PhysicalNumber operator+(const PhysicalNumber&) const;
   		const PhysicalNumber operator-(const PhysicalNumber&) const;
   		PhysicalNumber& operator+=(const PhysicalNumber&);
   		PhysicalNumber& operator-=(const PhysicalNumber&);
   		PhysicalNumber& operator=(const PhysicalNumber&);

   		friend bool operator==(const PhysicalNumber&, const PhysicalNumber&);
   		friend bool operator<(const PhysicalNumber&, const PhysicalNumber&);
   		friend bool operator!=(const PhysicalNumber&, const PhysicalNumber&);
   		friend bool operator<=(const PhysicalNumber&,const PhysicalNumber&);
   		friend bool operator>=(const PhysicalNumber&,const PhysicalNumber&);
   		friend bool operator>(const PhysicalNumber&,const PhysicalNumber&);
   		/*
   		Postfix
         */
   		const PhysicalNumber operator++(int);
   		const PhysicalNumber operator--(int);
         /*
         Prefix
         */
   		PhysicalNumber& operator++();
   		PhysicalNumber& operator--();

   		friend std::ostream& operator<<(std::ostream&, const PhysicalNumber&);
   		friend std::istream& operator>>(std::istream&, PhysicalNumber&);


   	/*
      Helping functions to determine if we work with same units
      */
   	static bool same_unit(const PhysicalNumber&, const PhysicalNumber&);
      static bool same_sub_unit(const PhysicalNumber&, const PhysicalNumber&);
   	static bool is_len(const PhysicalNumber&);
      static bool is_mass(const PhysicalNumber&);
   	static bool is_time(const PhysicalNumber&);
      /*
      Convert Functions
      */
      static double CM_TO_M(double  CM) {return CM/100; }
      static double CM_TO_KM(double CM) { return CM/100000;}
      static double M_TO_CM(double M) { return M*100; }
      static double M_TO_KM(double M) { return M/1000; }
      static double KM_TO_CM(double KM) { return KM*100000; }
      static double KM_TO_M(double KM) { return KM*1000; }

      static double G_TO_KG(double G) { return G/1000; }
      static double G_TO_TON(double G) { return G/1000000; }
      static double KG_TO_G(double KG) { return KG*1000; }
      static double KG_TO_TON(double KG) { return KG/1000; }
      static double TON_TO_G(double T) { return T*1000000; }
      static double TON_TO_KG(double T) { return T*1000; }

      static double SEC_TO_MIN(double S) { return S/60; }
      static double SEC_TO_HOUR(double S) { return S/3600; }
      static double MIN_TO_SEC(double M) { return M*60; }
      static double MIN_TO_HOUR(double M) { return M/60; }
      static double HOUR_TO_SEC(double H) { return H*3600; }
      static double HOUR_TO_MIN(double H) { return H*60; }


      };
}
#endif
