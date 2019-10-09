#define BOOST_TEST_ALTERNATIVE_INIT_API
#undef BOOST_TEST_MAIN
#define BOOST_TEST_NO_MAIN

#include <boost/test/unit_test.hpp>
#include <boost/test/framework.hpp>
#include <boost/test/unit_test_suite.hpp>

#include <iostream>

#include "Framework/Messenger/Messenger.h"
#include "Framework/Utils/RunOpt.h"

using namespace std;
using namespace genie;
using namespace boost::unit_test;

extern bool init_unit_test_suite( /* int argc, char *argv[] */ );

int main( int argc, char *argv[] )
{

   // try to silence GENIE Messenger just a little bit...
   //
   Messenger::Instance()->SetPrioritiesFromXmlFile("Messenger_whisper.xml");
   
/* this is an old(er) approach, before RunOpt::SetTuneName method was available
   RunOpt::Instance()->ReadFromCommandLine(0,0);
   if ( ! RunOpt::Instance() -> Tune() ) {
     LOG("gunittest", pFATAL) << " No TuneId in RunOption";
     exit(-1);
   }
   RunOpt::Instance() -> Tune() -> Build() ;
*/      

   RunOpt::Instance()->SetTuneName(); // It'll be "Default" which in v3.x.y is G18_02a
//   cout << RunOpt::Instance()->Tune()->Name() << endl;

   cout << "***** Starting Unit Tests *****" << endl;
   
   return unit_test_main( &init_unit_test_suite, argc, argv );

}
