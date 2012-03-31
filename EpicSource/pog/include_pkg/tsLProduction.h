//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tsLProduction.h
//
// Compiler-generated export header for package "tsLProduction"
//
// Revision control information:
//
// $Header: /flux/src/compiler/TypeChecker.cpp 31    27/03/01 14:31 Will $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype tsLProduction.Init();

prototype tsLProduction.Create( hisim producer, int type, int funds, int loss, int loans, bool active );

prototype tsLProduction.Save( hisim producer );

prototype tsLProduction.Restore( hisim producer );

prototype tsLProduction.SetActive( hisim producer, bool operational );

prototype bool tsLProduction.IsActive( hisim producer );

prototype int tsLProduction.GetType( hisim producer );

prototype tsLProduction.SetType( hisim producer, int prod_type );

prototype int tsLProduction.GetFunds( hisim producer );

prototype tsLProduction.SetFunds( hisim producer, int funds );

prototype int tsLProduction.GetLoans( hisim producer );

prototype tsLProduction.SetLoans( hisim producer, int loans );

prototype int tsLProduction.GetLoss( hisim producer );

prototype tsLProduction.SetLoss( hisim producer, int loss );

prototype hisim tsLProduction.FindById( int id );

// EOF /////////////////////////////////////////////////////////////////////////

