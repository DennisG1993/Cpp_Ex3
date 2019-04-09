/**
 * Examples of automatic tests for the exercise on physical numbers.
 *
 * @author Erel Segal-Halevi
 * @since 2019-02
 */

#include <iostream>
#include <sstream>
using std::cout, std::endl, std::istringstream;
#include "PhysicalNumber.h"
using ariel::PhysicalNumber, ariel::Unit;
#include "badkan.hpp"

int main() {
  badkan::TestCase testcase;
  int grade=0;
  int signal = setjmp(badkan::longjmp_buffer);
  if (signal == 0) {

    // BASIC TESTS - DO NOT CHANGE
    PhysicalNumber a(2, Unit::KM);
    PhysicalNumber b(300, Unit::M);
    PhysicalNumber c(2, Unit::HOUR);
    PhysicalNumber d(30, Unit::MIN);
    /*My Physical numbers for testing*/
    PhysicalNumber min1(37, Unit::MIN);
    PhysicalNumber min2(7, Unit::MIN);
    PhysicalNumber min3(23, Unit::MIN);
    PhysicalNumber sec1(2, Unit::SEC);
    PhysicalNumber sec2(8, Unit::SEC);
    PhysicalNumber sec3(14, Unit::SEC);
    PhysicalNumber hour1(9, Unit::HOUR);
    PhysicalNumber hour2(78, Unit::HOUR);
    PhysicalNumber hour3(32, Unit::HOUR);
    PhysicalNumber gram1(11, Unit::G);
    PhysicalNumber gram2(0, Unit::G);
    PhysicalNumber gram3(64, Unit::G);
    PhysicalNumber gram4(69444, Unit::G);
    PhysicalNumber kg1(27, Unit::KG);
    PhysicalNumber kg2(21, Unit::KG);
    PhysicalNumber kg3(73, Unit::KG);
    PhysicalNumber ton1(42, Unit::TON);
    PhysicalNumber ton2(532, Unit::TON);
    PhysicalNumber ton3(201, Unit::TON);
    PhysicalNumber cm1(277, Unit::CM);
    PhysicalNumber cm2(3602, Unit::CM);
    PhysicalNumber cm3(72, Unit::CM);
    PhysicalNumber meter1(92, Unit::M);
    PhysicalNumber meter2(54, Unit::M);
    PhysicalNumber meter3(55, Unit::M);
    PhysicalNumber km1(12, Unit::KM);
    PhysicalNumber km2(11, Unit::KM);
    PhysicalNumber km3(43, Unit::KM);

    testcase
    .setname("Basic output")
    .CHECK_OUTPUT(a, "2[km]")
    .CHECK_OUTPUT(b, "300[m]")

    .setname("Compatible dimensions")
    .CHECK_OUTPUT(b+a, "2300[m]")
    .CHECK_OUTPUT((a+=b), "2.3[km]")
    .CHECK_OUTPUT(a, "2.3[km]")
    .CHECK_OUTPUT(a+a, "4.6[km]")
    .CHECK_OUTPUT(b-b, "0[m]")
    .CHECK_OUTPUT(c, "2[hour]")
    .CHECK_OUTPUT(d, "30[min]")
    .CHECK_OUTPUT(d+c, "150[min]")

    .setname("Incompatible dimensions")
    .CHECK_THROWS(a+c)
    .CHECK_THROWS(a+d)
    .CHECK_THROWS(b+c)
    .CHECK_THROWS(b+d)

    .setname("Basic input")
    .CHECK_OK(istringstream("700[kg]") >> a)
    .CHECK_OUTPUT((a += PhysicalNumber(1, Unit::TON)), "1700[kg]")

    // YOUR TESTS - INSERT AS MANY AS YOU WANT
    //Check throws
    .CHECK_THROWS(min1+gram1)
    .CHECK_THROWS(min2+gram1)
    .CHECK_THROWS(min3+gram1)
    .CHECK_THROWS(min1+gram2)
    .CHECK_THROWS(min1+cm1)
    .CHECK_THROWS(min1+meter1)
    .CHECK_THROWS(min1+meter2)
    .CHECK_THROWS(min1+ton1)

    .CHECK_THROWS(hour1+gram1)
    .CHECK_THROWS(min2+ton2)
    .CHECK_THROWS(sec3+kg2)
    .CHECK_THROWS(cm2+gram2)
    .CHECK_THROWS(km3+ton2)
    .CHECK_THROWS(meter2+kg3)
    .CHECK_THROWS(cm1+ton2)
    .CHECK_THROWS(ton2+hour3)
    .CHECK_THROWS(cm1+=hour2)
    .CHECK_THROWS(hour3+=ton1)
    .CHECK_THROWS(meter2-=sec3)
    /********************************************************************************************************************************************/
    /********* Check Output***********/
    .CHECK_OUTPUT(min1 + sec2, "37.1333[min]")
    .CHECK_OUTPUT(min2 + hour3, "1927[min]")
    .CHECK_OUTPUT(sec3 + min3, "1394[sec]")
    .CHECK_OUTPUT(sec1 + hour1, "32402[sec]")
    .CHECK_OUTPUT(hour1 + hour2 + min2, "87.1167[hour]")
    .CHECK_OUTPUT(hour3 + sec2, "32.0022[hour]")
    .CHECK_OUTPUT(gram1 + kg2, "21011[g]")
    .CHECK_OUTPUT(gram3 + ton1, "4.20001e+07[g]")
    .CHECK_OUTPUT(kg1 + gram2, "27[kg]")
    .CHECK_OUTPUT(kg3 + ton2, "532073[kg]")
    .CHECK_OUTPUT(ton2 + gram4, "532.069[ton]")
    .CHECK_OUTPUT(ton3 + kg3, "201.073[ton]")
    .CHECK_OUTPUT(cm1 + km2, "1.10028e+06[cm]")
    .CHECK_OUTPUT(cm3 + meter2 , "5472[cm]")
    .CHECK_OUTPUT(meter2 + cm3, "54.72[m]")
    .CHECK_OUTPUT(meter3 + km1, "12055[m]")
    .CHECK_OUTPUT(km2 + meter1, "11.092[km]")
    .CHECK_OUTPUT(km1 + cm2, "12.036[km]")
    /********************************************************************************************************************************************/
    /********* Check OK***********/
    .CHECK_OK(istringstream("700[kg]") >> ton1)
    .CHECK_OK(istringstream("700[kg]") >> kg2)
    .CHECK_OK(istringstream("700[kg]") >> gram3)
    .CHECK_OK(istringstream("700[sec]") >> min2)
    .CHECK_OK(istringstream("700[min]") >> sec3)
    .CHECK_OK(istringstream("700[hour]") >> hour1)
    .CHECK_OK(cout<< min2)
    .CHECK_OK(cout<< kg2)
    .CHECK_OK(cout<< meter1)
    .CHECK_OK(cout<< hour3)
    .CHECK_OK(hour3+=sec2)
    .CHECK_OK(hour3-=min1)
    .CHECK_OK(ton1+=ton1)
    .CHECK_OK(hour3++)
    .CHECK_OK(hour3--)
    .CHECK_OK(++hour3)
    .CHECK_OK(--hour3)









      .setname("...")

      .print(cout, /*show_grade=*/false);
      grade = testcase.grade();
    } else {
      testcase.print_signal(signal);
      grade = 0;
    }
    cout <<  "*** Grade: " << grade << " ***" << endl;
    return grade;
}
