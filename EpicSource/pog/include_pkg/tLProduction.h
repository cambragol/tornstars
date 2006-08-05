//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tLProduction.h
//
// Compiler-generated export header for package "tLProduction"
//
// Revision control information:
//
// $Header: c:/epic/cvs/EpicSource/pog/include_pkg/tLProduction.h,v 1.2 2005/05/13 09:42:04 Owner Exp $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype tLProduction.Init();

prototype tLProduction.Create( hisim producer, int type, int funds, int loss, int loans, bool active );

prototype tLProduction.Save( hisim producer );

prototype tLProduction.Restore( hisim producer );

prototype tLProduction.SetActive( hisim producer, bool operational );

prototype bool tLProduction.IsActive( hisim producer );

prototype int tLProduction.GetType( hisim producer );

prototype tLProduction.SetType( hisim producer, int prod_type );

prototype int tLProduction.GetFunds( hisim producer );

prototype tLProduction.SetFunds( hisim producer, int funds );

prototype int tLProduction.GetLoans( hisim producer );

prototype tLProduction.SetLoans( hisim producer, int loans );

prototype int tLProduction.GetLoss( hisim producer );

prototype tLProduction.SetLoss( hisim producer, int loss );

prototype hisim tLProduction.FindById( int id );

// EOF /////////////////////////////////////////////////////////////////////////

