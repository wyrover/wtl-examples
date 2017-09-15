// CGraphExampleView.cpp : implementation of the CCGraphExampleView class
//

#include "stdafx.h"
#include "CGraphExample.h"

#include "CGraphExampleDoc.h"
#include "CGraphExampleView.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCGraphExampleView

IMPLEMENT_DYNCREATE(CCGraphExampleView, CView)

BEGIN_MESSAGE_MAP(CCGraphExampleView, CView)
    //{{AFX_MSG_MAP(CCGraphExampleView)
    //}}AFX_MSG_MAP
    // Standard printing commands
    ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCGraphExampleView construction/destruction

CCGraphExampleView::CCGraphExampleView()
{
    // TODO: add construction code here
}

CCGraphExampleView::~CCGraphExampleView()
{
    m_pGraphObject1->DestroyWindow();
    m_pGraphObject2->DestroyWindow();
    m_pGraphObject3->DestroyWindow();
    m_pGraphObject4->DestroyWindow();
    m_pGraphObject5->DestroyWindow();
    m_pGraphObject6->DestroyWindow();
    m_pGraphObject7->DestroyWindow();
    m_pGraphObject8->DestroyWindow();
    m_pGraphObject9->DestroyWindow();
    m_pGraphObject10->DestroyWindow();
    m_pGraphObject11->DestroyWindow();
    m_pGraphObject12->DestroyWindow();
    delete m_pGraphObject1;
    delete m_pGraphObject2;
    delete m_pGraphObject3;
    delete m_pGraphObject4;
    delete m_pGraphObject5;
    delete m_pGraphObject6;
    delete m_pGraphObject7;
    delete m_pGraphObject8;
    delete m_pGraphObject9;
    delete m_pGraphObject10;
    delete m_pGraphObject11;
    delete m_pGraphObject12;
}

BOOL CCGraphExampleView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs
    return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCGraphExampleView drawing

void CCGraphExampleView::OnDraw(CDC* pDC)
{
    CCGraphExampleDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    // TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CCGraphExampleView printing

BOOL CCGraphExampleView::OnPreparePrinting(CPrintInfo* pInfo)
{
    // default preparation
    return DoPreparePrinting(pInfo);
}

void CCGraphExampleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add extra initialization before printing
}

void CCGraphExampleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCGraphExampleView diagnostics

#ifdef _DEBUG
void CCGraphExampleView::AssertValid() const
{
    CView::AssertValid();
}

void CCGraphExampleView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CCGraphExampleDoc* CCGraphExampleView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCGraphExampleDoc)));
    return (CCGraphExampleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCGraphExampleView message handlers

void CCGraphExampleView::OnInitialUpdate()
{
    CView::OnInitialUpdate();
    // TODO: Add your specialized code here and/or call the base class
    // Create CGraphObject1 ( 2DPie graph )
    m_pGraphObject1 = new CGraphObject();
    m_pGraphObject1->Create(NULL, NULL, NULL, CRect(40, 20, 240, 220), this, ID_OBJECT_GRAPH_1, NULL);
    // Create graph and set graph parameters
    m_pGraphObject1->CreateGraph(GT_2DPIE);
    m_pGraphObject1->SetGraphBackgroundColor(RGB(255, 255, 255));
    m_pGraphObject1->SetGraphTitle("2DPie No. 1");
    m_pGraphObject1->SetGraphSubtitle("animation - none");
    m_pGraphObject1->SetGraphTitleShadow(FALSE);
    m_pGraphObject1->SetGraphSubtitleShadow(FALSE);
    m_pGraphObject1->SetGraphTitleColor(RGB(128, 128, 128));
    m_pGraphObject1->SetGraphSubtitleColor(RGB(96, 96, 96));
    m_pGraphObject1->SetGraphLegendBackgroundColor(RGB(208, 208, 208));
    // Add graph segments
    m_pGraphObject1->Add2DPieGraphSegment(40, RGB(255, 0, 0), "Seg_1");
    m_pGraphObject1->Add2DPieGraphSegment(25, RGB(0, 255, 0), "Seg_2");
    m_pGraphObject1->Add2DPieGraphSegment(15, RGB(0, 0, 255), "Seg_3");
    m_pGraphObject1->Add2DPieGraphSegment(5, RGB(255, 0, 255), "Seg_4");
    m_pGraphObject1->Add2DPieGraphSegment(8, RGB(0, 255, 255), "Seg_5");
    m_pGraphObject1->Add2DPieGraphSegment(7, RGB(255, 255, 0), "Seg_6");
    // Set graph animation
    m_pGraphObject1->SetGraphAnimation(FALSE, AT_PIE_DRAW);
    // Create CGraphObject2 ( 2DPie graph )
    m_pGraphObject2 = new CGraphObject();
    m_pGraphObject2->Create(NULL, NULL, NULL, CRect(280, 20, 480, 220), this, ID_OBJECT_GRAPH_2, NULL);
    // Create graph and set graph parameters
    m_pGraphObject2->CreateGraph(GT_2DPIE);
    m_pGraphObject2->SetGraphTitle("2DPie No. 2");
    m_pGraphObject2->SetGraphSubtitle("animation - draw");
    m_pGraphObject2->SetGraphFillType(GB_GRADIENT);
    m_pGraphObject2->SetGraphGradientColors(RGB(125, 0, 0), RGB(255, 255, 255));
    m_pGraphObject2->SetGraphTitleColor(RGB(196, 196, 196));
    m_pGraphObject2->SetGraphSubtitleColor(RGB(0, 0, 128));
    // Add graph segments
    m_pGraphObject2->Add2DPieGraphSegment(40, RGB(255, 0, 0), "Seg_1");
    m_pGraphObject2->Add2DPieGraphSegment(25, RGB(0, 255, 0), "Seg_2");
    // Set graph animation
    m_pGraphObject2->SetGraphAnimation(TRUE, AT_PIE_DRAW);
    // Create CGraphObject3 ( 2DPie graph )
    m_pGraphObject3 = new CGraphObject();
    m_pGraphObject3->Create(NULL, NULL, NULL, CRect(520, 20, 720, 220), this, ID_OBJECT_GRAPH_3, NULL);
    // Create graph and set graph parameters
    m_pGraphObject3->CreateGraph(GT_2DPIE);
    m_pGraphObject3->SetGraphBackgroundColor(RGB(196, 196, 128));
    m_pGraphObject3->SetGraphTitle("2DPie No. 3");
    m_pGraphObject3->SetGraphSubtitle("animation - blend");
    // Add graph segments
    m_pGraphObject3->Add2DPieGraphSegment(40, RGB(255, 0, 0), "Seg_1");
    m_pGraphObject3->Add2DPieGraphSegment(25, RGB(0, 255, 0), "Seg_2");
    m_pGraphObject3->Add2DPieGraphSegment(15, RGB(0, 0, 255), "Seg_3");
    m_pGraphObject3->Add2DPieGraphSegment(5, RGB(255, 0, 255), "Seg_4");
    // Set graph animation
    m_pGraphObject3->SetGraphAnimation(TRUE, AT_PIE_BLEND);
    // Create CGraphObject4 ( 2DBar graph )
    m_pGraphObject4 = new CGraphObject();
    m_pGraphObject4->Create(NULL, NULL, NULL, CRect(760, 20, 960, 220), this, ID_OBJECT_GRAPH_4, NULL);
    // Create graph and set graph parameters
    m_pGraphObject4->CreateGraph(GT_2DBAR);
    m_pGraphObject4->SetGraphBackgroundColor(RGB(196, 196, 196));
    m_pGraphObject4->SetGraphTitle("2DBar No. 1");
    m_pGraphObject4->SetGraphSubtitle("animation - none");
    // Add graph segments
    m_pGraphObject4->Add2DBarGraphSegment("Seg. 1");
    // Add graph series
    m_pGraphObject4->Add2DBarGraphSeries("Series 1", RGB(255, 0, 0));
    m_pGraphObject4->Add2DBarGraphSeries("Series 2", RGB(0, 255, 0));
    m_pGraphObject4->Add2DBarGraphSeries("Series 3", RGB(0, 0, 255));
    // Set graph series values
    m_pGraphObject4->Set2DBarGraphValue(1, 1, 100);
    m_pGraphObject4->Set2DBarGraphValue(1, 2, 50);
    m_pGraphObject4->Set2DBarGraphValue(1, 3, 20);
    // Set graph animation
    m_pGraphObject4->SetGraphAnimation(FALSE, AT_BAR_DRAW_ALL);
    // Create CGraphObject5 ( 2DBar graph )
    m_pGraphObject5 = new CGraphObject();
    m_pGraphObject5->Create(NULL, NULL, NULL, CRect(40, 240, 240, 440), this, ID_OBJECT_GRAPH_5, NULL);
    // Create graph and set graph parameters
    m_pGraphObject5->CreateGraph(GT_2DBAR);
    m_pGraphObject5->SetGraphBackgroundColor(RGB(196, 196, 128));
    m_pGraphObject5->SetGraphTitle("2DBar No. 2");
    m_pGraphObject5->SetGraphSubtitle("animation - draw_all");
    // Add graph segments
    m_pGraphObject5->Add2DBarGraphSegment("Seg. 1");
    m_pGraphObject5->Add2DBarGraphSegment("Seg. 2");
    m_pGraphObject5->Add2DBarGraphSegment("Seg. 3");
    // Add graph series
    m_pGraphObject5->Add2DBarGraphSeries("Series 1", RGB(255, 0, 0));
    m_pGraphObject5->Add2DBarGraphSeries("Series 2", RGB(0, 255, 0));
    m_pGraphObject5->Add2DBarGraphSeries("Series 3", RGB(0, 0, 255));
    // Set graph series values
    m_pGraphObject5->Set2DBarGraphValue(1, 1, 100);
    m_pGraphObject5->Set2DBarGraphValue(2, 1, 90);
    m_pGraphObject5->Set2DBarGraphValue(3, 1, 70);
    m_pGraphObject5->Set2DBarGraphValue(1, 2, 50);
    m_pGraphObject5->Set2DBarGraphValue(2, 2, 40);
    m_pGraphObject5->Set2DBarGraphValue(3, 2, 60);
    m_pGraphObject5->Set2DBarGraphValue(1, 3, 20);
    m_pGraphObject5->Set2DBarGraphValue(2, 3, 30);
    m_pGraphObject5->Set2DBarGraphValue(3, 3, 40);
    // Set graph animation
    m_pGraphObject5->SetGraphAnimation(TRUE, AT_BAR_DRAW_ALL);
    // Create CGraphObject6 ( 2DBar graph )
    m_pGraphObject6 = new CGraphObject();
    m_pGraphObject6->Create(NULL, NULL, NULL, CRect(280, 240, 480, 440), this, ID_OBJECT_GRAPH_6, NULL);
    // Create graph and set graph parameters
    m_pGraphObject6->CreateGraph(GT_2DBAR);
    m_pGraphObject6->SetGraphBackgroundColor(RGB(196, 196, 128));
    m_pGraphObject6->SetGraphTitle("2DBar No. 3");
    m_pGraphObject6->SetGraphSubtitle("animation - draw_segment");
    m_pGraphObject6->SetGraphTitleShadow(TRUE);
    m_pGraphObject6->SetGraphSubtitleShadow(TRUE);
    // Add graph segments
    m_pGraphObject6->Add2DBarGraphSegment("Seg. 1");
    m_pGraphObject6->Add2DBarGraphSegment("Seg. 2");
    m_pGraphObject6->Add2DBarGraphSegment("Seg. 3");
    // Add graph series
    m_pGraphObject6->Add2DBarGraphSeries("Series 1", RGB(255, 0, 0));
    m_pGraphObject6->Add2DBarGraphSeries("Series 2", RGB(0, 255, 0));
    // Set graph series values
    m_pGraphObject6->Set2DBarGraphValue(1, 1, 100);
    m_pGraphObject6->Set2DBarGraphValue(2, 1, 90);
    m_pGraphObject6->Set2DBarGraphValue(3, 1, 70);
    m_pGraphObject6->Set2DBarGraphValue(1, 2, 50);
    m_pGraphObject6->Set2DBarGraphValue(2, 2, 40);
    m_pGraphObject6->Set2DBarGraphValue(3, 2, 60);
    // Set graph animation
    m_pGraphObject6->SetGraphAnimation(TRUE, AT_BAR_DRAW_SEGMENT);
    // Create CGraphObject7 ( 2DBar graph )
    m_pGraphObject7 = new CGraphObject();
    m_pGraphObject7->Create(NULL, NULL, NULL, CRect(520, 240, 720, 440), this, ID_OBJECT_GRAPH_7, NULL);
    // Create graph and set graph parameters
    m_pGraphObject7->CreateGraph(GT_2DBAR);
    m_pGraphObject7->SetGraphBackgroundColor(RGB(196, 196, 128));
    m_pGraphObject7->SetGraphTitle("2DBar No. 4");
    m_pGraphObject7->SetGraphSubtitle("animation - draw_series");
    // Add graph segments
    m_pGraphObject7->Add2DBarGraphSegment("Seg. 1");
    m_pGraphObject7->Add2DBarGraphSegment("Seg. 2");
    m_pGraphObject7->Add2DBarGraphSegment("Seg. 3");
    // Add graph series
    m_pGraphObject7->Add2DBarGraphSeries("Series 1", RGB(255, 0, 0));
    m_pGraphObject7->Add2DBarGraphSeries("Series 2", RGB(0, 255, 0));
    m_pGraphObject7->Add2DBarGraphSeries("Series 3", RGB(0, 0, 255));
    // Set graph series values
    m_pGraphObject7->Set2DBarGraphValue(1, 1, 100);
    m_pGraphObject7->Set2DBarGraphValue(2, 1, 90);
    m_pGraphObject7->Set2DBarGraphValue(3, 1, 70);
    m_pGraphObject7->Set2DBarGraphValue(1, 2, 50);
    m_pGraphObject7->Set2DBarGraphValue(2, 2, 40);
    m_pGraphObject7->Set2DBarGraphValue(3, 2, 60);
    m_pGraphObject7->Set2DBarGraphValue(1, 3, 20);
    m_pGraphObject7->Set2DBarGraphValue(2, 3, 30);
    m_pGraphObject7->Set2DBarGraphValue(3, 3, 40);
    // Set graph animation
    m_pGraphObject7->SetGraphAnimation(TRUE, AT_BAR_DRAW_SERIES);
    // Create CGraphObject8 ( 2DBar graph )
    m_pGraphObject8 = new CGraphObject();
    m_pGraphObject8->Create(NULL, NULL, NULL, CRect(760, 240, 960, 440), this, ID_OBJECT_GRAPH_8, NULL);
    // Create graph and set graph parameters
    m_pGraphObject8->CreateGraph(GT_2DBAR);
    m_pGraphObject8->SetGraphTitle("2DBar No. 5");
    m_pGraphObject8->SetGraphSubtitle("animation - blend_segment");
    m_pGraphObject8->SetGraphFillType(GB_GRADIENT);
    m_pGraphObject8->SetGraphGradientColors(RGB(255, 255, 255), RGB(0, 0, 125));
    m_pGraphObject8->SetGradientFillType(FT_HORIZONTAL);
    m_pGraphObject8->SetGraphTitleShadow(FALSE);
    m_pGraphObject8->SetGraphSubtitleShadow(FALSE);
    // Add graph segments
    m_pGraphObject8->Add2DBarGraphSegment("Seg. 1");
    m_pGraphObject8->Add2DBarGraphSegment("Seg. 2");
    m_pGraphObject8->Add2DBarGraphSegment("Seg. 3");
    // Add graph series
    m_pGraphObject8->Add2DBarGraphSeries("Series 1", RGB(255, 0, 0));
    m_pGraphObject8->Add2DBarGraphSeries("Series 2", RGB(0, 255, 0));
    m_pGraphObject8->Add2DBarGraphSeries("Series 3", RGB(0, 0, 255));
    // Set graph series values
    m_pGraphObject8->Set2DBarGraphValue(1, 1, 100);
    m_pGraphObject8->Set2DBarGraphValue(2, 1, 90);
    m_pGraphObject8->Set2DBarGraphValue(3, 1, 70);
    m_pGraphObject8->Set2DBarGraphValue(1, 2, 50);
    m_pGraphObject8->Set2DBarGraphValue(2, 2, 40);
    m_pGraphObject8->Set2DBarGraphValue(3, 2, 60);
    m_pGraphObject8->Set2DBarGraphValue(1, 3, 20);
    m_pGraphObject8->Set2DBarGraphValue(2, 3, 30);
    m_pGraphObject8->Set2DBarGraphValue(3, 3, 40);
    // Set graph animation
    m_pGraphObject8->SetGraphAnimation(TRUE, AT_BAR_BLEND_SEGMENT);
    // Create CGraphObject9 ( 2DBar graph )
    m_pGraphObject9 = new CGraphObject();
    m_pGraphObject9->Create(NULL, NULL, NULL, CRect(40, 460, 240, 660), this, ID_OBJECT_GRAPH_9, NULL);
    // Create graph and set graph parameters
    m_pGraphObject9->CreateGraph(GT_2DBAR);
    m_pGraphObject9->SetGraphBackgroundColor(RGB(196, 196, 128));
    m_pGraphObject9->SetGraphTitle("2DBar No. 6");
    m_pGraphObject9->SetGraphSubtitle("animation - blend_series");
    m_pGraphObject9->SetGraphLegendBackgroundColor(RGB(164, 164, 128));
    // Add graph segments
    m_pGraphObject9->Add2DBarGraphSegment("Seg. 1");
    m_pGraphObject9->Add2DBarGraphSegment("Seg. 2");
    m_pGraphObject9->Add2DBarGraphSegment("Seg. 3");
    // Add graph series
    m_pGraphObject9->Add2DBarGraphSeries("Series 1", RGB(255, 0, 0));
    m_pGraphObject9->Add2DBarGraphSeries("Series 2", RGB(0, 255, 0));
    // Set graph series values
    m_pGraphObject9->Set2DBarGraphValue(1, 1, 100);
    m_pGraphObject9->Set2DBarGraphValue(2, 1, 90);
    m_pGraphObject9->Set2DBarGraphValue(3, 1, 70);
    m_pGraphObject9->Set2DBarGraphValue(1, 2, 50);
    m_pGraphObject9->Set2DBarGraphValue(2, 2, 40);
    m_pGraphObject9->Set2DBarGraphValue(3, 2, 60);
    // Set graph animation
    m_pGraphObject9->SetGraphAnimation(TRUE, AT_BAR_BLEND_SERIES);
    // Create CGraphObject10 ( 2DLine graph )
    m_pGraphObject10 = new CGraphObject();
    m_pGraphObject10->Create(NULL, NULL, NULL, CRect(280, 460, 480, 660), this, ID_OBJECT_GRAPH_10, NULL);
    // Create graph and set graph parameters
    m_pGraphObject10->CreateGraph(GT_2DLINE);
    m_pGraphObject10->SetGraphBackgroundColor(RGB(128, 128, 96));
    m_pGraphObject10->SetGraphTitle("2DLine No. 1");
    m_pGraphObject10->SetGraphSubtitle("animation - none");
    // Add graph segments
    m_pGraphObject10->Add2DLineGraphSegment("Seg. 1");
    m_pGraphObject10->Add2DLineGraphSegment("Seg. 2");
    m_pGraphObject10->Add2DLineGraphSegment("Seg. 3");
    m_pGraphObject10->Add2DLineGraphSegment("Seg. 4");
    m_pGraphObject10->Add2DLineGraphSegment("Seg. 5");
    // Add graph series
    m_pGraphObject10->Add2DLineGraphSeries("Series 1", RGB(255, 0, 0));
    m_pGraphObject10->Add2DLineGraphSeries("Series 2", RGB(255, 255, 0));
    m_pGraphObject10->Add2DLineGraphSeries("Series 3", RGB(0, 0, 255));
    // Set graph series values
    m_pGraphObject10->Set2DLineGraphValue(1, 1, 100);
    m_pGraphObject10->Set2DLineGraphValue(2, 1, 90);
    m_pGraphObject10->Set2DLineGraphValue(3, 1, 70);
    m_pGraphObject10->Set2DLineGraphValue(4, 1, 50);
    m_pGraphObject10->Set2DLineGraphValue(5, 1, 80);
    m_pGraphObject10->Set2DLineGraphValue(1, 2, 50);
    m_pGraphObject10->Set2DLineGraphValue(2, 2, 40);
    m_pGraphObject10->Set2DLineGraphValue(3, 2, 60);
    m_pGraphObject10->Set2DLineGraphValue(4, 2, 40);
    m_pGraphObject10->Set2DLineGraphValue(5, 2, 10);
    m_pGraphObject10->Set2DLineGraphValue(1, 3, 20);
    m_pGraphObject10->Set2DLineGraphValue(2, 3, 30);
    m_pGraphObject10->Set2DLineGraphValue(3, 3, 40);
    m_pGraphObject10->Set2DLineGraphValue(4, 3, 10);
    m_pGraphObject10->Set2DLineGraphValue(5, 3, 50);
    // Set graph animation
    m_pGraphObject10->SetGraphAnimation(FALSE, AT_LINE_DRAW_ALL);
    // Create CGraphObject11 ( 2DLine graph )
    m_pGraphObject11 = new CGraphObject();
    m_pGraphObject11->Create(NULL, NULL, NULL, CRect(520, 460, 720, 660), this, ID_OBJECT_GRAPH_11, NULL);
    // Create graph and set graph parameters
    m_pGraphObject11->CreateGraph(GT_2DLINE);
    m_pGraphObject11->SetGraphTitle("2DLine No. 2");
    m_pGraphObject11->SetGraphSubtitle("animation - draw_all");
    m_pGraphObject11->SetGraphFillType(GB_GRADIENT);
    m_pGraphObject11->SetGraphGradientColors(RGB(0, 125, 0), RGB(196, 196, 0));
    m_pGraphObject11->SetGraphTitleShadow(FALSE);
    m_pGraphObject11->SetGraphSubtitleShadow(FALSE);
    m_pGraphObject11->SetGraphSubtitleColor(RGB(196, 196, 196));
    m_pGraphObject11->SetGraphLabelsColor(RGB(255, 255, 255));
    // Add graph segments
    m_pGraphObject11->Add2DLineGraphSegment("Seg. 1");
    m_pGraphObject11->Add2DLineGraphSegment("Seg. 2");
    m_pGraphObject11->Add2DLineGraphSegment("Seg. 3");
    m_pGraphObject11->Add2DLineGraphSegment("Seg. 4");
    m_pGraphObject11->Add2DLineGraphSegment("Seg. 5");
    // Add graph series
    m_pGraphObject11->Add2DLineGraphSeries("Series 1", RGB(255, 0, 0));
    m_pGraphObject11->Add2DLineGraphSeries("Series 2", RGB(255, 255, 0));
    m_pGraphObject11->Add2DLineGraphSeries("Series 3", RGB(0, 0, 255));
    // Set graph series values
    m_pGraphObject11->Set2DLineGraphValue(1, 1, 100);
    m_pGraphObject11->Set2DLineGraphValue(2, 1, 90);
    m_pGraphObject11->Set2DLineGraphValue(3, 1, 70);
    m_pGraphObject11->Set2DLineGraphValue(4, 1, 50);
    m_pGraphObject11->Set2DLineGraphValue(5, 1, 80);
    m_pGraphObject11->Set2DLineGraphValue(1, 2, 50);
    m_pGraphObject11->Set2DLineGraphValue(2, 2, 40);
    m_pGraphObject11->Set2DLineGraphValue(3, 2, 60);
    m_pGraphObject11->Set2DLineGraphValue(4, 2, 40);
    m_pGraphObject11->Set2DLineGraphValue(5, 2, 10);
    m_pGraphObject11->Set2DLineGraphValue(1, 3, 20);
    m_pGraphObject11->Set2DLineGraphValue(2, 3, 30);
    m_pGraphObject11->Set2DLineGraphValue(3, 3, 40);
    m_pGraphObject11->Set2DLineGraphValue(4, 3, 10);
    m_pGraphObject11->Set2DLineGraphValue(5, 3, 50);
    // Set graph animation
    m_pGraphObject11->SetGraphAnimation(TRUE, AT_LINE_DRAW_ALL);
    // Create CGraphObject12 ( 2DLine graph )
    m_pGraphObject12 = new CGraphObject();
    m_pGraphObject12->Create(NULL, NULL, NULL, CRect(760, 460, 960, 660), this, ID_OBJECT_GRAPH_12, NULL);
    // Create graph and set graph parameters
    m_pGraphObject12->CreateGraph(GT_2DLINE);
    m_pGraphObject12->SetGraphBackgroundColor(RGB(196, 196, 128));
    m_pGraphObject12->SetGraphTitle("2DLine No. 3");
    m_pGraphObject12->SetGraphSubtitle("animation - draw_series");
    m_pGraphObject12->SetGraphLegendBackgroundColor(RGB(208, 208, 208));
    m_pGraphObject12->SetGraphTitleShadow(TRUE);
    m_pGraphObject12->SetGraphSubtitleShadow(TRUE);
    // Add graph segments
    m_pGraphObject12->Add2DLineGraphSegment("Seg. 1");
    m_pGraphObject12->Add2DLineGraphSegment("Seg. 2");
    m_pGraphObject12->Add2DLineGraphSegment("Seg. 3");
    m_pGraphObject12->Add2DLineGraphSegment("Seg. 4");
    m_pGraphObject12->Add2DLineGraphSegment("Seg. 5");
    // Add graph series
    m_pGraphObject12->Add2DLineGraphSeries("Series 1", RGB(255, 0, 0));
    m_pGraphObject12->Add2DLineGraphSeries("Series 2", RGB(255, 255, 0));
    m_pGraphObject12->Add2DLineGraphSeries("Series 3", RGB(0, 0, 255));
    // Set graph series values
    m_pGraphObject12->Set2DLineGraphValue(1, 1, 100);
    m_pGraphObject12->Set2DLineGraphValue(2, 1, 90);
    m_pGraphObject12->Set2DLineGraphValue(3, 1, 70);
    m_pGraphObject12->Set2DLineGraphValue(4, 1, 50);
    m_pGraphObject12->Set2DLineGraphValue(5, 1, 80);
    m_pGraphObject12->Set2DLineGraphValue(1, 2, 50);
    m_pGraphObject12->Set2DLineGraphValue(2, 2, 40);
    m_pGraphObject12->Set2DLineGraphValue(3, 2, 60);
    m_pGraphObject12->Set2DLineGraphValue(4, 2, 40);
    m_pGraphObject12->Set2DLineGraphValue(5, 2, 10);
    m_pGraphObject12->Set2DLineGraphValue(1, 3, 20);
    m_pGraphObject12->Set2DLineGraphValue(2, 3, 30);
    m_pGraphObject12->Set2DLineGraphValue(3, 3, 40);
    m_pGraphObject12->Set2DLineGraphValue(4, 3, 10);
    m_pGraphObject12->Set2DLineGraphValue(5, 3, 50);
    // Set graph animation
    m_pGraphObject12->SetGraphAnimation(TRUE, AT_LINE_DRAW_SERIES);
}
