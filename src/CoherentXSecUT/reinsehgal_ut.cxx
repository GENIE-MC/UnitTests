
#include "CommonCOHXSec.h"

using namespace std;
using namespace genie;
using namespace boost::unit_test;

#include "SynthEvent.h"

#include "Framework/Utils/RunOpt.h"
#include "Physics/Coherent/XSection/ReinSehgalCOHPiPXSec.h"

void reinsehgal_ut()
{

   double tolerance_in_percent = 0.001;

   string tune_name = RunOpt::Instance()->Tune()->Name();
   
   if ( tune_name.find("G00_00a") == string::npos )
   {
      RunOpt::Instance()->SetTuneName("G00_00a_00_000" );
   }
   
   EventRecord* synth_event = new SynthEventCOH();

   ReinSehgalCOHPiPXSec* rs = new ReinSehgalCOHPiPXSec();

   BOOST_CHECK( rs != 0 );

   rs->Configure("Default" );
   
   BOOST_CHECK( rs->ValidProcess( synth_event->Summary() ) );

   double xsec = rs->XSec( synth_event->Summary(), kPSxyfE );

   BOOST_REQUIRE_NE( xsec, 0. );
   
   // ---> cout << " RS XSec = " << xsec << endl;
   
   BOOST_CHECK_CLOSE( xsec, 1.74145e-11, tolerance_in_percent );
   
   // now modifiy parameter(s) and check again
   //
   
   // fisrt of all, get model config (registry) 
   // and create custom registry from it
   //

   Registry config_modi( rs->GetConfig() );

   // now change parameter itself
   //
   
   string ModPCACPath = "COH-UseModifiedPCAC";
//   bool ModPCAC = (rs_xsec->GetConfig()).GetBool(ModPCACPath);
//   cout << " ModPCAC = " << ModPCAC << endl;
   config_modi.Set( ModPCACPath, false );

   // reconfigure the RS XSec object with the new config
   //
   
   rs->Configure( config_modi );
   
   // recalculate RS XSec
   //
   
   xsec = rs->XSec( synth_event->Summary(), kPSxyfE ); 
//   cout << " Modified RS XSec(modi) = " << xsec << endl;   

   // make sure (via boost) that xsec is valid (non-zero)
   //
   
   BOOST_REQUIRE_NE( xsec, 0. );
      
   // check (via boost) if the (modified) xsec value 
   // is within tolerance of the expected number
   //
   
   BOOST_CHECK_CLOSE( xsec,  2.00335e-11, tolerance_in_percent );

   // set tune name back to "Default"
   //
   
   RunOpt::Instance()->SetTuneName(); // or maybe SetTuneName(tune_name)
   
   delete rs;
   delete synth_event;
   
   return;

}