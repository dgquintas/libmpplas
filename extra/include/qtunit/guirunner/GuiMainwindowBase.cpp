/****************************************************************************
** Form implementation generated from reading ui file 'guirunner/GuiMainwindowBase.ui'
**
** Created: Sun Jan 28 14:23:20 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "GuiMainwindowBase.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qsplitter.h>
#include <qheader.h>
#include <qlistview.h>
#include <qgroupbox.h>
#include <qprogressbar.h>
#include <qlabel.h>
#include <qframe.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qaction.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qtoolbar.h>
#include <qimage.h>
#include <qpixmap.h>

#include "qmessagebox.h"
#include "qapplication.h"
#include "GuiMainwindowBase.ui.h"
static const char* const image0_data[] = { 
"22 22 41 1",
". c None",
"h c #000000",
"F c #181818",
"g c #242424",
"A c #3a3a3a",
"f c #3d3d3d",
"e c #484848",
"d c #4a4a4a",
"c c #4c4c4c",
"b c #555555",
"a c #676767",
"# c #797979",
"M c #929292",
"t c #959595",
"J c #a6a6a6",
"E c #b5b5b5",
"s c #b6b6b6",
"z c #bbbbbb",
"x c #bcbcbc",
"w c #bfbfbf",
"L c #c1c1c1",
"I c #c5c5c5",
"K c #cccccc",
"r c #d7d7d7",
"D c #dadada",
"q c #dcdcdc",
"p c #dfdfdf",
"y c #e2e2e2",
"v c #e3e3e3",
"l c #e5e5e5",
"H c #e7e7e7",
"j c #e9e9e9",
"o c #ededed",
"G c #efefef",
"k c #f0f0f0",
"C c #f1f1f1",
"n c #f7f7f7",
"u c #f9f9f9",
"B c #fdfdfd",
"m c #fefefe",
"i c #ffffff",
"......................",
"....#abcddefgh........",
"...#iiiiiiiiihh.......",
"...aiiiiiiiiihjh......",
"...biiiiiiiiihklh.....",
"...ciiiiiiiimhnoph....",
"...diiiiiiiiihhhhhh...",
"...diiiiiiiiiiqrsth...",
"...diiiiiiiiiiiuvwh...",
"...diiiiiiiiiiiuvxh...",
"...diiiiiiiiiiiuvxh...",
"...diiiiiiiiiiiuvxh...",
"...diiiiiiiiiiiuvxh...",
"...diiiiiiiiiiiuvxh...",
"...diiiiiiiiiiiuvxh...",
"...eiiiiiiiiiiiuyzh...",
"...AiiBuuuuuuuuCDEh...",
"...FBGHvvvvvvvyDIJh...",
"...hpKLxxxxxxxzEJMh...",
"....hhhhhhhhhhhhhh....",
"......................",
"......................"};

static const char* const image1_data[] = { 
"22 22 83 2",
"Qt c None",
".b c #000000",
".c c #030303",
".a c #040404",
".V c #060606",
".p c #090909",
".f c #0b0b0b",
".W c #0d0d0d",
".# c #161616",
".q c #171717",
".u c #1e1e1e",
"#. c #1f1f1f",
".r c #222222",
".e c #242424",
".t c #262626",
".s c #272727",
".U c #282828",
".M c #292929",
".G c #2e2e2e",
"#q c #313100",
"#k c #353500",
"#f c #363600",
".v c #373737",
".9 c #383800",
".d c #3c3c3c",
"#p c #3d3d00",
".6 c #404000",
".k c #424242",
"#o c #464600",
"#j c #474700",
".g c #474747",
"#n c #494900",
"#e c #4a4a00",
".2 c #4c4c00",
"#m c #4d4d00",
".5 c #525200",
"#l c #555500",
"#i c #575700",
"#d c #5d5d00",
".1 c #5f5f00",
".8 c #606000",
".4 c #646400",
"#h c #676700",
"#c c #6b6b00",
".7 c #6e6e00",
".0 c #6f6f00",
".3 c #707000",
"#b c #717100",
"#a c #747400",
".Z c #757500",
".Y c #777700",
".X c #787800",
".T c #c2c243",
".L c #c6c665",
".F c #d1d16a",
".S c #d7d74a",
".R c #e4e44f",
".O c #e4e450",
".P c #e4e451",
".Q c #e4e452",
"## c #e5e553",
".K c #e9e976",
"#g c #f2f27b",
".E c #f4f47c",
".z c #f4f47d",
".o c #f4f47e",
".J c #f4f47f",
".j c #f4f480",
".A c #f4f481",
".y c #f5f583",
".N c #f5f584",
".B c #f5f585",
".I c #f5f586",
".n c #f5f587",
".C c #f5f589",
".D c #f5f58a",
".x c #f5f58b",
".i c #f5f58c",
".H c #f6f68e",
".m c #f6f693",
".w c #f6f694",
".h c #f6f699",
".l c #f7f79c",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQt.#.a.bQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.c.bQt.b.bQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQt.b.bQtQtQt.b.bQtQt.bQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.b.bQt",
"QtQt.d.e.fQtQtQtQtQtQtQtQtQtQtQtQtQt.b.b.bQt",
"Qt.g.h.i.j.bQtQtQtQtQtQtQtQtQtQtQt.b.b.b.bQt",
".k.l.m.n.o.b.p.q.r.s.t.u.f.bQtQtQtQtQtQtQtQt",
".v.w.x.y.o.z.A.B.C.x.D.n.E.F.bQtQtQtQtQtQtQt",
".G.H.I.j.z.z.J.A.y.y.y.j.K.L.bQtQtQtQtQtQtQt",
".M.x.N.J.E.O.O.P.Q.Q.Q.R.S.T.bQtQtQtQtQtQtQt",
".U.x.y.o.E.R.R.b.b.b.b.b.b.b.b.b.V.W.c.b.b.b",
".U.x.y.o.R.R.b.X.X.X.X.X.Y.Z.Z.Y.Y.0.1.2.bQt",
".U.x.y.o.R.b.X.X.X.X.X.X.X.Y.Z.3.4.5.6.bQtQt",
".s.D.y.Q.b.X.X.X.X.X.X.X.X.Z.7.8.2.9.bQtQtQt",
"#..I##.b#a#a#a#a#a#a#a#a#b#c#d#e#f.bQtQtQtQt",
".W#g.b#h.4.4.4.4.4.4.4.4.8#i#j#k.bQtQtQtQtQt",
".b.b#l#m#e#e#e#e#e#e#e#n#o#p#q.bQtQtQtQtQtQt",
"Qt.b.b.b.b.b.b.b.b.b.b.b.b.b.bQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt"};

static const char* const image2_data[] = { 
"22 22 76 2",
"Qt c None",
".h c #000000",
".K c #080808",
".F c #090909",
".v c #0b0b0b",
".A c #131313",
".g c #181818",
".t c #1a1a1a",
".n c #262626",
".r c #272727",
".f c #3a3a3a",
".k c #444444",
".e c #484848",
".d c #4a4a4a",
"#j c #4b4b00",
".c c #4c4c4c",
"#e c #545400",
".b c #555555",
".H c #585800",
".W c #595900",
"#i c #5a5a00",
".C c #5b5b00",
".2 c #5c5c00",
".6 c #5e5e00",
".x c #606000",
".U c #676700",
".a c #676767",
"#d c #686800",
".p c #696900",
".P c #6a6a00",
".L c #6b6b00",
".X c #6c6c00",
"#a c #6d6d00",
".T c #6e6e00",
".V c #6f6f00",
".w c #707000",
".S c #717100",
".O c #737300",
".1 c #747400",
".R c #757500",
".o c #777700",
".Q c #787800",
".# c #797979",
".N c #7c7c08",
".8 c #7e7e0b",
"#h c #7e7e7e",
"#g c #848484",
".4 c #858519",
".J c #86861a",
".E c #86861b",
"#f c #8b8b8b",
".7 c #8c8c26",
".z c #8d8d27",
"#c c #919191",
".3 c #949434",
".I c #959536",
".D c #969638",
".q c #98983c",
".y c #9c9c44",
"## c #9d9d9d",
".0 c #a0a0a0",
".j c #a7a759",
"#b c #a7a7a7",
"#. c #aaaaaa",
".5 c #afafaf",
".Z c #b0b0b0",
".i c #b4b471",
".9 c #b8b8b8",
".Y c #bcbcbc",
".M c #c0c0c0",
".G c #c1c1c1",
".B c #c3c3c3",
".u c #c7c7c7",
".s c #c8c8c8",
".m c #cecece",
".l c #cfcfcf",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQt.#.a.b.c.d.d.d.d.d.d.d.d.d.d.e.f.g.hQtQt",
"Qt.#.i.j.k.l.m.m.m.m.m.m.m.m.m.m.m.n.o.p.hQt",
"Qt.a.j.q.r.s.t.t.t.t.t.t.t.t.t.t.u.v.w.x.hQt",
"Qt.b.y.z.A.B.B.B.B.B.B.B.B.B.B.B.B.h.h.C.hQt",
"Qt.c.D.E.F.G.h.h.h.h.h.h.h.h.h.h.G.h.h.H.hQt",
"Qt.d.I.J.K.G.G.G.G.G.G.G.G.G.G.G.G.h.L.H.hQt",
"Qt.d.I.J.K.G.h.h.h.h.h.h.h.h.h.h.G.h.L.H.hQt",
"Qt.d.I.J.K.G.G.G.G.G.G.G.G.G.G.G.G.h.L.H.hQt",
"Qt.d.I.J.K.G.h.h.h.h.h.h.h.h.h.h.G.h.L.H.hQt",
"Qt.d.I.J.K.G.G.G.G.G.G.G.G.G.M.M.M.h.L.H.hQt",
"Qt.d.I.J.N.h.h.h.h.h.h.h.h.h.h.h.h.O.P.H.hQt",
"Qt.d.I.J.N.Q.Q.Q.Q.Q.Q.Q.Q.R.S.T.w.w.p.H.hQt",
"Qt.d.I.J.N.Q.Q.Q.Q.Q.Q.Q.o.S.L.U.P.V.P.W.hQt",
"Qt.d.I.J.N.h.h.h.h.h.h.h.h.h.h.h.h.w.X.C.hQt",
"Qt.d.I.J.N.h.h.h.h.h.h.h.Y.Z.0.h.h.1.w.2.hQt",
"Qt.e.3.4.N.h.h.h.h.h.h.h.Y.5.0.h.h.Q.O.6.hQt",
"Qt.f.7.8.o.h.h.h.h.h.h.h.9#.##.h.h.o.S.C.hQt",
"Qt.g.o.w#a.h.h.h.h.h.h.h#b###c.h.h.V#d#e.hQt",
"Qt.h.p.x.C.h.h.h.h.h.h.h#f#g#h.h.h.x#i#j.hQt",
"QtQt.h.h.h.h.h.h.h.h.h.h.h.h.h.h.h.h.h.hQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt"};

static const char* const image3_data[] = { 
"22 22 92 2",
"Qt c None",
".v c #000000",
".P c #020156",
".Z c #030157",
".I c #03015a",
"#f c #03015b",
".N c #03015c",
".5 c #03015d",
".U c #03015f",
".F c #030160",
".B c #030162",
".z c #030163",
".M c #030166",
"#s c #030167",
".H c #03026a",
".A c #03026c",
".q c #030270",
"#k c #030272",
".r c #030273",
".y c #030275",
".k c #030278",
".t c #030279",
".s c #040279",
".p c #04027b",
".G c #04027e",
".j c #04027f",
".O c #040281",
".i c #040283",
".h c #040285",
"#v c #040287",
".Y c #040288",
".E c #040289",
".g c #04028a",
"#e c #05038a",
".x c #0c0a8e",
".c c #0d0b8e",
"#l c #0e0e0e",
".o c #131191",
".m c #171717",
"#r c #1b1995",
".4 c #1c1a95",
".b c #27269b",
".T c #29289b",
".9 c #2b2a9c",
".f c #2d2c9d",
"#g c #323232",
"#. c #434343",
".d c #444444",
".a c #4543a8",
".w c #4846aa",
".C c #484848",
".J c #494949",
".l c #4a4a4a",
".X c #4b49ab",
".3 c #514fae",
".n c #5957b1",
".e c #5f5db4",
".# c #6463b7",
"#z c #a09ca0",
"#y c #afaaaf",
"#d c #b1acb1",
"#c c #bfbabf",
"#q c #c7c2c7",
"#p c #cac4ca",
"#w c #cdc7cd",
".8 c #d2ccd2",
"#m c #d3cdd3",
"#b c #d4ced4",
"#u c #d7d1d7",
"#o c #d8d2d8",
"#n c #dcd6dc",
"#j c #ddd7dd",
".7 c #e0dae0",
".2 c #e3dde3",
".S c #e5dfe5",
"#t c #e7e1e7",
"#a c #e8e2e8",
".L c #e9e3e9",
"#i c #eae4ea",
"#x c #ece6ec",
".1 c #ede6ed",
".W c #efe8ef",
"#h c #f0e9f0",
".R c #f3ecf3",
".D c #f5eef5",
".0 c #f6eff6",
".6 c #f9f2f9",
"## c #faf3fa",
".V c #fbf4fb",
".K c #fdf6fd",
".Q c #fff8ff",
".u c #fff9ff",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQt.#.a.b.cQtQtQtQt",
"QtQtQt.dQtQtQtQtQtQtQtQtQt.e.f.g.h.i.j.kQtQt",
"QtQtQt.l.mQtQtQtQtQtQtQt.n.o.p.q.r.s.t.qQtQt",
"QtQtQt.l.u.vQtQtQtQtQt.w.x.y.zQtQt.t.t.A.BQt",
"QtQtQt.C.u.D.vQtQtQtQt.E.y.FQtQtQtQt.G.H.IQt",
"QtQtQt.J.u.K.L.vQtQtQt.t.M.NQtQtQtQt.O.M.PQt",
"QtQtQt.J.u.Q.R.S.vQtQtQtQtQtQtQtQt.T.p.UQtQt",
"QtQtQt.l.u.u.V.W.S.vQtQtQtQtQtQt.X.Y.A.ZQtQt",
"QtQtQt.l.u.u.Q.0.1.2.vQtQtQtQt.3.4.y.5QtQtQt",
"QtQtQt.J.u.u.Q.6.W.7.8.vQtQtQt.9.j.zQtQtQtQt",
"QtQtQt#..u.Q##.R#a#b#c#d.vQtQt#e.r#fQtQtQtQt",
"QtQtQt#g.Q#h#i#a#j.v.v.v.v.vQt.Y#k.5QtQtQtQt",
"QtQtQt#l#a#m.v#n#o.vQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQt.v#p.vQt.v#n#q.vQtQtQtQt#r.p#sQtQtQtQt",
"QtQtQt.v.vQtQt.v#t#u.vQtQtQtQt#v#k.FQtQtQtQt",
"QtQtQt.vQtQtQtQt.v.S#w.vQtQtQt.s.M.IQtQtQtQt",
"QtQtQtQtQtQtQtQt.v#x#m.vQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQt.v#w#y.vQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQt.v#c#z.vQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQt.v.vQtQtQtQtQtQtQtQtQtQt"};


/*
 *  Constructs a GuiMainwindowBase as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 */
GuiMainwindowBase::GuiMainwindowBase( QWidget* parent, const char* name, WFlags fl )
    : QMainWindow( parent, name, fl ),
      image0( (const char **) image0_data ),
      image1( (const char **) image1_data ),
      image2( (const char **) image2_data ),
      image3( (const char **) image3_data )
{
    (void)statusBar();
    if ( !name )
	setName( "GuiMainwindowBase" );
    setCentralWidget( new QWidget( this, "qt_central_widget" ) );
    GuiMainwindowBaseLayout = new QVBoxLayout( centralWidget(), 11, 6, "GuiMainwindowBaseLayout"); 

    mpSplitter = new QSplitter( centralWidget(), "mpSplitter" );
    mpSplitter->setFrameShape( QSplitter::NoFrame );
    mpSplitter->setFrameShadow( QSplitter::Plain );
    mpSplitter->setOrientation( QSplitter::Horizontal );

    mpTestsListview = new QListView( mpSplitter, "mpTestsListview" );
    mpTestsListview->addColumn( tr( "Tests" ) );
    mpTestsListview->header()->setClickEnabled( FALSE, mpTestsListview->header()->count() - 1 );
    mpTestsListview->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)7, 0, 0, mpTestsListview->sizePolicy().hasHeightForWidth() ) );
    mpTestsListview->setMinimumSize( QSize( 240, 0 ) );
    mpTestsListview->setFrameShape( QListView::StyledPanel );
    mpTestsListview->setFrameShadow( QListView::Sunken );
    mpTestsListview->setSelectionMode( QListView::Extended );
    mpTestsListview->setResizeMode( QListView::AllColumns );
    mpTestsListview->setTreeStepSize( 0 );

    QWidget* privateLayoutWidget = new QWidget( mpSplitter, "mpRunLayout" );
    mpRunLayout = new QVBoxLayout( privateLayoutWidget, 6, 6, "mpRunLayout"); 

    mpProgressGroupBox = new QGroupBox( privateLayoutWidget, "mpProgressGroupBox" );
    mpProgressGroupBox->setColumnLayout(0, Qt::Vertical );
    mpProgressGroupBox->layout()->setSpacing( 6 );
    mpProgressGroupBox->layout()->setMargin( 11 );
    mpProgressGroupBoxLayout = new QVBoxLayout( mpProgressGroupBox->layout() );
    mpProgressGroupBoxLayout->setAlignment( Qt::AlignTop );

    mpProgressbar = new QProgressBar( mpProgressGroupBox, "mpProgressbar" );
    mpProgressbar->setProgress( 0 );
    mpProgressGroupBoxLayout->addWidget( mpProgressbar );

    mpStatsLayout = new QHBoxLayout( 0, 0, 6, "mpStatsLayout"); 

    mpRunsLabel = new QLabel( mpProgressGroupBox, "mpRunsLabel" );
    mpStatsLayout->addWidget( mpRunsLabel );

    mpRunsStats = new QLabel( mpProgressGroupBox, "mpRunsStats" );
    mpStatsLayout->addWidget( mpRunsStats );

    mpErrorsLabel = new QLabel( mpProgressGroupBox, "mpErrorsLabel" );
    mpStatsLayout->addWidget( mpErrorsLabel );

    mpErrorsStats = new QLabel( mpProgressGroupBox, "mpErrorsStats" );
    mpStatsLayout->addWidget( mpErrorsStats );

    mpFailuresLabel = new QLabel( mpProgressGroupBox, "mpFailuresLabel" );
    mpStatsLayout->addWidget( mpFailuresLabel );

    mpFailuresStats = new QLabel( mpProgressGroupBox, "mpFailuresStats" );
    mpStatsLayout->addWidget( mpFailuresStats );
    mpProgressGroupBoxLayout->addLayout( mpStatsLayout );
    mpRunLayout->addWidget( mpProgressGroupBox );

    mpErrorsGroupbox = new QGroupBox( privateLayoutWidget, "mpErrorsGroupbox" );
    mpErrorsGroupbox->setColumnLayout(0, Qt::Vertical );
    mpErrorsGroupbox->layout()->setSpacing( 6 );
    mpErrorsGroupbox->layout()->setMargin( 11 );
    mpErrorsGroupboxLayout = new QHBoxLayout( mpErrorsGroupbox->layout() );
    mpErrorsGroupboxLayout->setAlignment( Qt::AlignTop );

    mpErrorsListview = new QListView( mpErrorsGroupbox, "mpErrorsListview" );
    mpErrorsListview->addColumn( tr( "Type" ) );
    mpErrorsListview->header()->setClickEnabled( FALSE, mpErrorsListview->header()->count() - 1 );
    mpErrorsListview->addColumn( tr( "Name" ) );
    mpErrorsListview->header()->setClickEnabled( FALSE, mpErrorsListview->header()->count() - 1 );
    mpErrorsListview->addColumn( tr( "Failed Condition" ) );
    mpErrorsListview->header()->setClickEnabled( FALSE, mpErrorsListview->header()->count() - 1 );
    mpErrorsListview->addColumn( tr( "File Name" ) );
    mpErrorsListview->header()->setClickEnabled( FALSE, mpErrorsListview->header()->count() - 1 );
    mpErrorsListview->addColumn( tr( "Line Number" ) );
    mpErrorsListview->header()->setClickEnabled( FALSE, mpErrorsListview->header()->count() - 1 );
    mpErrorsListview->setResizePolicy( QListView::AutoOneFit );
    mpErrorsListview->setAllColumnsShowFocus( TRUE );
    mpErrorsListview->setResizeMode( QListView::LastColumn );
    mpErrorsGroupboxLayout->addWidget( mpErrorsListview );
    mpRunLayout->addWidget( mpErrorsGroupbox );
    GuiMainwindowBaseLayout->addWidget( mpSplitter );

    mpHorizLine = new QFrame( centralWidget(), "mpHorizLine" );
    mpHorizLine->setProperty( "frameShape", "HLine" );
    mpHorizLine->setFrameShadow( QFrame::Sunken );
    mpHorizLine->setFrameShape( QFrame::HLine );
    GuiMainwindowBaseLayout->addWidget( mpHorizLine );

    mpMainButtonsLayout = new QHBoxLayout( 0, 0, 6, "mpMainButtonsLayout"); 

    mpRunButton = new QPushButton( centralWidget(), "mpRunButton" );
    mpRunButton->setEnabled( FALSE );
    mpMainButtonsLayout->addWidget( mpRunButton );

    mpRunselectedButton = new QPushButton( centralWidget(), "mpRunselectedButton" );
    mpRunselectedButton->setEnabled( FALSE );
    mpRunselectedButton->setAccel( QKeySequence( 276824147 ) );
    mpMainButtonsLayout->addWidget( mpRunselectedButton );

    mpStopButton = new QPushButton( centralWidget(), "mpStopButton" );
    mpStopButton->setEnabled( FALSE );
    mpMainButtonsLayout->addWidget( mpStopButton );

    mpQuitButton = new QPushButton( centralWidget(), "mpQuitButton" );
    mpMainButtonsLayout->addWidget( mpQuitButton );
    GuiMainwindowBaseLayout->addLayout( mpMainButtonsLayout );

    // actions
    mpHelpContentsAction = new QAction( this, "mpHelpContentsAction" );
    mpHelpContentsAction->setAccel( 4144 );
    mpHelpIndexAction = new QAction( this, "mpHelpIndexAction" );
    mpHelpIndexAction->setAccel( 0 );
    mpHelpAboutAction = new QAction( this, "mpHelpAboutAction" );
    mpHelpAboutAction->setAccel( 0 );
    mpFileQuitAction = new QAction( this, "mpFileQuitAction" );
    mpFileQuitAction->setAccel( 272629841 );
    mpFilePreferencesAction = new QAction( this, "mpFilePreferencesAction" );
    mpFilePreferencesAction->setAccel( 4194384 );
    mpProjectNew = new QAction( this, "mpProjectNew" );
    mpProjectNew->setIconSet( QIconSet( image0 ) );
    mpProjectNew->setAccel( 4194382 );
    mpProjectOpen = new QAction( this, "mpProjectOpen" );
    mpProjectOpen->setIconSet( QIconSet( image1 ) );
    mpProjectOpen->setAccel( 4194383 );
    mpProjectClose = new QAction( this, "mpProjectClose" );
    mpProjectClose->setEnabled( FALSE );
    mpProjectClose->setAccel( 4194391 );
    mpProjectProperties = new QAction( this, "mpProjectProperties" );
    mpProjectProperties->setEnabled( FALSE );
    mpProjectSave = new QAction( this, "mpProjectSave" );
    mpProjectSave->setEnabled( FALSE );
    mpProjectSave->setIconSet( QIconSet( image2 ) );
    mpProjectSave->setAccel( 4194387 );
    mpHelpWhatsThis = new QAction( this, "mpHelpWhatsThis" );
    mpHelpWhatsThis->setIconSet( QIconSet( image3 ) );
    mpHelpWhatsThis->setAccel( 2101296 );


    // toolbars


    // menubar
    mpMenubar = new QMenuBar( this, "mpMenubar" );

    mpMenubar->setEnabled( TRUE );

    mpFileMenu = new QPopupMenu( this );
    mpFilePreferencesAction->addTo( mpFileMenu );
    mpFileMenu->insertSeparator();
    mpFileQuitAction->addTo( mpFileMenu );
    mpMenubar->insertItem( QString(""), mpFileMenu, 2 );

    mpPopupMenu = new QPopupMenu( this );
    mpProjectNew->addTo( mpPopupMenu );
    mpProjectOpen->addTo( mpPopupMenu );
    mpPopupMenu->insertSeparator();
    mpProjectClose->addTo( mpPopupMenu );
    mpPopupMenu->insertSeparator();
    mpProjectSave->addTo( mpPopupMenu );
    mpPopupMenu->insertSeparator();
    mpProjectProperties->addTo( mpPopupMenu );
    mpMenubar->insertItem( QString(""), mpPopupMenu, 3 );

    mpHelpMenu = new QPopupMenu( this );
    mpHelpAboutAction->addTo( mpHelpMenu );
    mpHelpMenu->insertSeparator();
    mpHelpWhatsThis->addTo( mpHelpMenu );
    mpMenubar->insertItem( QString(""), mpHelpMenu, 4 );

    languageChange();
    resize( QSize(676, 498).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( mpQuitButton, SIGNAL( clicked() ), this, SLOT( quit() ) );
    connect( mpRunselectedButton, SIGNAL( clicked() ), this, SLOT( runSelectedTests() ) );
    connect( mpStopButton, SIGNAL( clicked() ), this, SLOT( stop() ) );
    connect( mpFileQuitAction, SIGNAL( activated() ), this, SLOT( quit() ) );
    connect( mpFilePreferencesAction, SIGNAL( activated() ), this, SLOT( showPreferences() ) );
    connect( mpHelpAboutAction, SIGNAL( activated() ), this, SLOT( helpAbout() ) );
    connect( mpErrorsListview, SIGNAL( doubleClicked(QListViewItem*) ), this, SLOT( showError(QListViewItem*) ) );
    connect( mpProjectNew, SIGNAL( activated() ), this, SLOT( projectNew() ) );
    connect( mpProjectClose, SIGNAL( activated() ), this, SLOT( projectClose() ) );
    connect( mpProjectSave, SIGNAL( activated() ), this, SLOT( projectSave() ) );
    connect( mpProjectOpen, SIGNAL( activated() ), this, SLOT( projectOpen() ) );
    connect( mpProjectProperties, SIGNAL( activated() ), this, SLOT( projectProperties() ) );
    connect( mpTestsListview, SIGNAL( selectionChanged() ), this, SLOT( testsSelected() ) );
    connect( mpTestsListview, SIGNAL( doubleClicked(QListViewItem*) ), this, SLOT( runOneTest(QListViewItem*) ) );
    connect( mpHelpWhatsThis, SIGNAL( activated() ), this, SLOT( whatsThis() ) );
    connect( mpRunButton, SIGNAL( clicked() ), this, SLOT( runAllTests() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
GuiMainwindowBase::~GuiMainwindowBase()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void GuiMainwindowBase::languageChange()
{
    setCaption( tr( "QtUnit" ) );
    mpTestsListview->header()->setLabel( 0, tr( "Tests" ) );
    QWhatsThis::add( mpTestsListview, tr( "The list of all the tests that are available in the currently opened project." ) );
    mpProgressGroupBox->setTitle( tr( "Progress" ) );
    QWhatsThis::add( mpProgressGroupBox, tr( "Displays the advancement of the test evaluations.<br>\n"
"<br>\n"
"Additionally, statistics about the amount of tests that have been executed and the number of errors and failures that occured are available." ) );
    mpRunsLabel->setText( tr( "Runs:" ) );
    mpRunsStats->setText( tr( "0" ) );
    mpErrorsLabel->setText( tr( "Errors:" ) );
    mpErrorsStats->setText( tr( "0" ) );
    mpFailuresLabel->setText( tr( "Failures:" ) );
    mpFailuresStats->setText( tr( "0" ) );
    mpErrorsGroupbox->setTitle( tr( "&Errors and failures" ) );
    QWhatsThis::add( mpErrorsGroupbox, tr( "The list of errors and failures that occured during the last run.<br>\n"
"<br>\n"
"Each entry contains the method name, the failed condition, the file name and the line number where the test wasn't successful." ) );
    mpErrorsListview->header()->setLabel( 0, tr( "Type" ) );
    mpErrorsListview->header()->setLabel( 1, tr( "Name" ) );
    mpErrorsListview->header()->setLabel( 2, tr( "Failed Condition" ) );
    mpErrorsListview->header()->setLabel( 3, tr( "File Name" ) );
    mpErrorsListview->header()->setLabel( 4, tr( "Line Number" ) );
    mpRunButton->setText( tr( " &Run all tests " ) );
    QWhatsThis::add( mpRunButton, tr( "Run all the tests in this project.<br>\n"
"<br>\n"
"If modules have been modified, they will be reloaded automatically and all the new tests will be run." ) );
    mpRunselectedButton->setText( tr( " Run &selected tests " ) );
    QWhatsThis::add( mpRunselectedButton, tr( "Run only the tests that have been selected in the listview.<br>\n"
"<br>\n"
"If modules have been modified, the tests will not be run but will be reloaded automatically. The selection will have to be made again." ) );
    mpStopButton->setText( tr( " Sto&p " ) );
    QWhatsThis::add( mpStopButton, tr( "Stops the execution of the tests." ) );
    mpQuitButton->setText( tr( " &Quit" ) );
    QWhatsThis::add( mpQuitButton, tr( "Quits the entire application." ) );
    mpHelpContentsAction->setText( tr( "Contents" ) );
    mpHelpContentsAction->setMenuText( tr( "&Contents..." ) );
    mpHelpIndexAction->setText( tr( "Index" ) );
    mpHelpIndexAction->setMenuText( tr( "&Index..." ) );
    mpHelpAboutAction->setText( tr( "About" ) );
    mpHelpAboutAction->setMenuText( tr( "&About..." ) );
    mpFileQuitAction->setText( tr( "Quit" ) );
    mpFileQuitAction->setMenuText( tr( "&Quit" ) );
    mpFilePreferencesAction->setText( tr( "Preferences" ) );
    mpFilePreferencesAction->setMenuText( tr( "&Preferences..." ) );
    mpProjectNew->setText( tr( "New" ) );
    mpProjectNew->setMenuText( tr( "&New..." ) );
    mpProjectOpen->setText( tr( "Open" ) );
    mpProjectOpen->setMenuText( tr( "&Open..." ) );
    mpProjectClose->setText( tr( "Close" ) );
    mpProjectClose->setMenuText( tr( "&Close" ) );
    mpProjectProperties->setText( tr( "Properties" ) );
    mpProjectProperties->setMenuText( tr( "&Properties..." ) );
    mpProjectSave->setText( tr( "Save" ) );
    mpProjectSave->setMenuText( tr( "&Save" ) );
    mpHelpWhatsThis->setText( tr( "What's this?" ) );
    mpHelpWhatsThis->setMenuText( tr( "&What's this?" ) );
    if (mpMenubar->findItem(2))
        mpMenubar->findItem(2)->setText( tr( "&File" ) );
    if (mpMenubar->findItem(3))
        mpMenubar->findItem(3)->setText( tr( "&Project" ) );
    if (mpMenubar->findItem(4))
        mpMenubar->findItem(4)->setText( tr( "&Help" ) );
}

