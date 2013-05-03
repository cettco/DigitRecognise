// bpDlg.h : header file
//

#if !defined(AFX_BPDLG_H__7652B1F9_3538_46A2_B5AE_CA84618C2354__INCLUDED_)
#define AFX_BPDLG_H__7652B1F9_3538_46A2_B5AE_CA84618C2354__INCLUDED_

#include "InputWnd.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CBpDlg dialog
#define N_BUF 101//����ά��  +1
#define O_BUF 4 //���ά��
#define C_BUF 6//���ز�ά��  +1
#define STUDY_SPEED 0.3//ѧϰ����
#define ALPHA    0.1 //�嶯ϵ��
#define EP       0.01 //�����ֵ
#define EP2      0.001
#define TEST_SETS   4
#define  EACH_LINE_OFFSET   40
#define max_layer   3 //�������
#define max_node    100 //�������Ľڵ���

class CBpDlg : public CDialog
{
// Construction
	 int N[3];//����Ľڵ���
	 double u[max_layer][max_node];//ĳһ��ĳһ�ڵ�����
	 double w[max_layer][max_node][max_node];//Ȩֵ
	 double temp_w_1[max_layer][max_node][max_node];//w(k-1)
	 double temp_w_2[max_layer][max_node][max_node];//w(k)
	
	 float input[N_BUF];//��������
	 int  output[O_BUF];//�������
	 int count;//������ȷ��������
	 FILE *fp;//�ļ�
	 FILE *	fpwucha;
	 double e[max_layer][max_node];//������u�ĵ���
	 double g[max_layer][max_node][max_node];//������w�ĵ��������ݶ�
	 int ceshishi;
	 double wucha;//���
	 int k_k;

public:
	void initial(FILE *fp);
	double erro();
	void update_weights();
	void compute_gradient();
	void feed_forward();
	double gf(int layer,int node);
	double f(int node,int layer);
	void init();
	CInputWnd m_wndInput;
	CBpDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBpDlg)
	enum { IDD = IDD_BP_DIALOG };
	CComboBox	m_wndComBox;
	CString	m_result;
	CString	m_err;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBpDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBpDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSampling();
	afx_msg void OnRun();
	afx_msg void OnTrain();
	afx_msg void OnClear();
	afx_msg void OnTrainByhand();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BPDLG_H__7652B1F9_3538_46A2_B5AE_CA84618C2354__INCLUDED_)
