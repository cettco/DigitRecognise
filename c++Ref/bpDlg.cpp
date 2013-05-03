// bpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "bp.h"
#include "bpDlg.h"
#include "function.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

double delta_w[max_layer][max_node][max_node];//冲动向量

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBpDlg dialog

CBpDlg::CBpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBpDlg)
	m_result = _T("");
	m_err = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	N[0]=N_BUF;
	N[1]=C_BUF;
	N[2]=O_BUF;
	ceshishi=0;
	wucha=1;//误差
	k_k=-1;
	count=0;
//	delta_w	=new double[max_layer*max_node*max_node];
	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBpDlg)
	DDX_Control(pDX, IDC_COMBO2, m_wndComBox);
	DDX_Text(pDX, IDC_EDIT1, m_result);
	DDX_Text(pDX, IDC_EDIT2, m_err);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBpDlg, CDialog)
	//{{AFX_MSG_MAP(CBpDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SAMPLING, OnSampling)
	ON_BN_CLICKED(IDC_RUN, OnRun)
	ON_BN_CLICKED(IDC_TRAIN, OnTrain)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	ON_BN_CLICKED(IDC_TRAIN_BYHAND, OnTrainByhand)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBpDlg message handlers

BOOL CBpDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
    m_wndInput.SubclassDlgItem (IDC_INPUTWND,this);
	m_wndInput.Initialization ();
	init();
	m_wndComBox.SetCurSel(0);
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBpDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBpDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBpDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBpDlg::init()
{
	FILE * fpw=NULL;
	if (!(fpw=fopen("权值.txt","r")))
	{
		for (int i0=0;i0<max_layer;i0++)
			for (int i1=0;i1<max_node;i1++)
				for (int i2=0;i2<max_node;i2++)
					w[i0][i1][i2]=randnumber();
	}
	else /////////////读取权值
	{
		for ( int i0=0;i0<max_layer;i0++)
			for ( int i1=0;i1<max_node;i1++)
				for ( int i2=0;i2<max_node;i2++)
				{
					fseek(fpw,11L,1);
					fscanf(fpw,"%f",&w[i0][i1][i2]);
				}
				
				fclose(fpw);
	}
	fpwucha=fopen("bp结果\\误差变化序列.txt","w");
	if (!fpwucha){
		MessageBox("cannot open file");
		exit(0);
	}
}

double CBpDlg::f(int node, int layer)//求某个节点的输出值
{
	double sum=0;
	for (int node2=0;node2<N[layer-1];node2++)
	{
		sum=sum+w[layer][node][node2]*u[layer-1][node2];
	}
	sum=1.0/(1+exp(0-sum));
	return sum;
	
}

double CBpDlg::gf(int layer, int node)//求误差函数对u的导数
{
	double sum=0;
	for (int m=0;m<N[layer+1];m++)
		sum=sum+e[layer+1][m]*u[layer+1][m]*(1-u[layer+1][m])*w[layer+1][m][node];
	return sum;
	
}

void CBpDlg::feed_forward()//前馈输出值
{
	for (int layer=1;layer<=2;layer++)
		for(int node=0;node<N[layer];node++)
			u[layer][node]=f(node,layer);
		
}

void CBpDlg::compute_gradient()//求梯度
{
	for (int layer=2;layer>0;layer--)
	{
		for(int node=0;node<N[layer];node++)
		{
			if (layer==2) e[2][node]=u[2][node]-output[node];
			else e[layer][node]=gf(layer,node);
		}
		
		for (int j=0;j<N[layer];j++)
			for(int i=0;i<N[layer-1];i++)
			{
                g[layer][j][i]=e[layer][j]*u[layer][j]*(1.0-u[layer][j])*u[layer-1][i];  
				
			}
	}
	
}

void CBpDlg::update_weights()//修改权值
{
	for (int layer=1;layer<=2;layer++)
		for (int j=0;j<N[layer];j++)
			for(int i=0;i<N[layer-1];i++)
			{
				temp_w_1[layer][j][i]=w[layer][j][i];
				w[layer][j][i]=w[layer][j][i]-STUDY_SPEED*g[layer][j][i]+ALPHA*delta_w[layer][j][i];
				temp_w_2[layer][j][i]=w[layer][j][i];
				delta_w[layer][j][i]=temp_w_2[layer][j][i]-temp_w_1[layer][j][i];
			}
}

double CBpDlg::erro()//误差
{
	double sum=0;
	for(int i=0;i<O_BUF;i++)
		sum+=pow(fabs(u[2][i]-output[i]),2);
	//sum=pow(fabs(u[2][0]-output[0]),2)+pow(fabs(u[2][1]-output[1]),2)+pow(fabs(u[2][2]-output[2]),2);
	
	return sum;
}

void CBpDlg::initial(FILE *fp)//从文件中读入标准化的样例供学习使用.
{
	if(feof(fp)) 
	{
		rewind(fp);
		k_k=(++k_k)%4;
		if(!k_k)  fprintf(fpwucha,"\n");
		fprintf(fpwucha,"%16f",wucha);
		wucha=0;
	}
	input[0]=1.0;
	for(int i=1;i<N_BUF;i++)
		fscanf(fp,"%f",input+i);
	
	for(i=0;i<O_BUF;i++)
		fscanf(fp,"%d",output+i);
	for(int k=0;k<N_BUF-1;k++)
		u[0][k]=input[k];
}


void CBpDlg::OnSampling() 
{
	// TODO: Add your control notification handler code here
	m_wndInput.GetInput (10);
	
}

void CBpDlg::OnRun() //识别数字
{
	m_wndInput.GetInput (10); //采样处理，将输入居中
	int result=0;
	BYTE input_temp[LEN][LEN];
	for(int i=0;i<LEN;i++)
		for(int j=0;j<LEN;j++)
			input_temp[i][j]=m_wndInput.m_InputArray[j][i];
	BYTE *a=(BYTE*)input_temp;
	for(i=1;i<N_BUF;i++)
		input[i]=(float)(*(a+i-1));
	for(int k=0;k<N_BUF-1;k++)
		u[0][k]=input[k];
	feed_forward();
	for(int m=0;m<O_BUF;m++){
		u[2][m]=floor(u[2][m]+0.5);
		result*=2;
		result+=u[2][m];
	}
	double err=erro()/2.0;//误差is here .
	m_result.Format("%d",result);
	m_err.Format("%f",err);
	this->UpdateData(FALSE);
	
}

void CBpDlg::OnTrain() 
{
//	init();
	// TODO: Add your control notification handler code here
	fp=fopen("study.txt","r");
	if (fp==NULL){
		MessageBox("cannot open file");;
		exit(0);
	}
//	printf("正在训练,请稍等.......");
	//开始时钟
	clock_t t1=clock();
	if (t1==clock_t(-1)){
		MessageBox("sorry ,no clock\n");
		exit(1);
	}
	while (wucha>EP){
		initial(fp);
		feed_forward();
		compute_gradient();
        update_weights();
		wucha+=erro();
	}
	//结束时钟
	clock_t t2=clock();
	if (t2==clock_t(-1)){
		MessageBox("sorry ,no clock\n");
		exit(1);
	}  
//	cout<<"\r"<<"        训练结束!            "<<endl;
//	cout<<""<<"     "<<double(t2-t1)/CLOCKS_PER_SEC<<"seconds"<<"(这个时间包括了读写文件时间，可以精确)"<<endl;
	CString mess;
	mess.Format("训练时间为:%fseconds",double(t2-t1)/CLOCKS_PER_SEC);
	MessageBox(mess);
   	fclose(fp);
    fclose(fpwucha);	
}

void CBpDlg::OnClear() 
{
	// TODO: Add your control notification handler code here
	for(int i=0;i<LEN;i++)
		for(int j=0;j<LEN;j++)
		{
			m_wndInput.m_bArray[i][j]=false;
		}
	this->Invalidate ();
}

void CBpDlg::OnTrainByhand() 
{
	m_wndInput.GetInput (10);
	int result=0;
	BYTE input_temp[LEN][LEN];
	for(int i=0;i<LEN;i++){
		for(int j=0;j<LEN;j++)
		{
			input_temp[i][j]=m_wndInput.m_InputArray[j][i];
			CString res;
			res.Format("%d  ",(int)input_temp[i][j]);
			TRACE(res);
		}
		TRACE("\n");
	}
		
/*
	m_wndInput.GetInput (10);
	int result=0;
	BYTE input_temp[LEN][LEN];
	for(int i=0;i<LEN;i++)
		for(int j=0;j<LEN;j++)
			input_temp[i][j]=m_wndInput.m_InputArray[j][i];
		BYTE *a=(BYTE*)input_temp;
		int num=0;
		while(wucha>EP&&num++<10000){
			int k=m_wndComBox.GetCurSel();
			output[0]=k&8?0:1;
			output[1]=k&4?0:1;
			output[2]=k&2?0:1;
			output[3]=k&1?0:1;
			for(i=1;i<N_BUF;i++)
			input[i]=(float)(*(a+i-1));
			for( k=0;k<N_BUF-1;k++)
				u[0][k]=input[k];
			feed_forward();
			update_weights();
			wucha+=erro();
		}
		*/

}
