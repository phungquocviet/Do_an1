#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <io.h>
#include <fcntl.h>
#pragma warning(disable:4996)
typedef struct
{
	wchar_t mssv[10];
	wchar_t name[30];
	wchar_t khoa[30];
	int nienkhoa;
	wchar_t ngaysinh[10];
	wchar_t linkimage[1000];
	wchar_t email[100];
	wchar_t mota[1000];
	wchar_t sothich1[32];
	wchar_t sothich2[32];
}sinhvien;
void readcsv_loai1(FILE*fpcsv, sinhvien &sv)		//tat ca cac truong duoc bao boi dau ngoac kep
{
	fwscanf(fpcsv, L"\"%[^\"]\",\"%[^\"]\",\"%[^\"]\",\"%d\",\"%[^\"]\",\"%[^\"]\",\"%[^\"]\",\"%[^\"]\",\"%[^\"]\",\"%[^\"]\"",
		&sv.mssv, &sv.name, &sv.khoa, &sv.nienkhoa, &sv.ngaysinh, &sv.linkimage, &sv.email, &sv.mota, &sv.sothich1, &sv.sothich2);
}
void writehtml(FILE* &fphtml, FILE* fphtml_goc, sinhvien sv)
{
	wchar_t name_htm[14];
	for (int i = 0; i <= wcslen(sv.mssv); i++)
	{
		name_htm[i] = sv.mssv[i];
	}
	wchar_t* fphtml_name = wcscat(name_htm, L".htm");
	fphtml = _wfopen(fphtml_name, L"wt, ccs=UTF-8");
	if (fphtml != NULL)
	{
		wchar_t str[1024];
		while (1)
		{
			fgetws(str, 1024, fphtml_goc);

			if (wcsstr(str, L"HCMUS - Nguyễn Văn A") != NULL)
			{
				fwprintf(fphtml, L"<title>HCMUS - %ls</title>", sv.name);
			}
			else if (wcsstr(str, L"NGUYENVANA - MSSV") != NULL)
			{
				fwprintf(fphtml, L"<span class=\"Personal_FullName\"> %ls - %ls </span>", sv.name, sv.mssv);
			}
			else if (wcsstr(str, L"CONGNGHETHONGTIN") != NULL)
			{
				fwprintf(fphtml, L"<div class=\"Personal_Department\">KHOA %ls</div>", (sv.khoa));
			}
			else if (wcsstr(str, L"nva1@gmail.com") != NULL)
			{
				fwprintf(fphtml, L"Email: %ls", sv.email);
			}
			else if (wcsstr(str, L"HinhCaNhan.jpg") != NULL)
			{
				fwprintf(fphtml, L"<img src=\"Images/%ls\" class=\"Personal_Hinhcanhan\" />", sv.linkimage);
			}
			else if (wcsstr(str, L"Nguyễn Văn A1") != NULL)
			{
				fwprintf(fphtml, L"<li>Họ và tên: %ls </li>\n", sv.name);
			}
			else if (wcsstr(str, L"1212123") != NULL)
			{
				fwprintf(fphtml, L"<li>MSSV: %ls </li>\n", sv.mssv);
			}
			else if (wcsstr(str, L"Công nghệ thông tin") != NULL)
			{
				fwprintf(fphtml, L"<li>Sinh viên khoa: %ls </li>\n", sv.khoa);
			}
			else if (wcsstr(str, L"20/01/1994") != NULL)
			{
				fwprintf(fphtml, L"<li>Ngày sinh : %ls </li>\n", sv.ngaysinh);
			}
			else if (wcsstr(str, L"nva2@gmail.com") != NULL)
			{
				fwprintf(fphtml, L"<li>Email : %ls</li>\n", sv.email);
			}
			else if (wcsstr(str, L"dayladongmota") != NULL)
			{
				fwprintf(fphtml, L"%ls", sv.mota);
			}
			else if (wcsstr(str, L"Âm nhạc") != NULL)
			{
				fwprintf(fphtml, L"<li>%ls</li>", sv.sothich1);
			}
			else if (wcsstr(str, L"Ẩm thực") != NULL)
			{
				fwprintf(fphtml, L"<li>%ls</li>", sv.sothich2);
			}
			else if (wcsstr(str, L"MSSV - Tên Sinh Viên Thực Hiện") != NULL)
			{
				fwprintf(fphtml, L"%ls - %ls </br>", sv.mssv, sv.name);
			}
			else
			{
				fwprintf(fphtml, L"%ls", str);
			}
			char ch = fgetwc(fphtml_goc);//kiem tra da doc het hay chua, neu da doc het htmlgoc.htm thi` break; neu chua het thi doi con tro sang trai 1L(vi` khi getc con tro da~dich sang phai 1L)
			if ((int)ch == -1)
				break;
			else
				fseek(fphtml_goc, -1, SEEK_CUR);
		}

	}
}

void main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	FILE* fpcsv;
	FILE* fphtml;
	FILE* fphtml_goc;

	wchar_t* fpcsv_name = L"sinhvien.csv";
	fpcsv = _wfopen(fpcsv_name, L"rt, ccs=UTF-8");		//Mo file CSV

	wchar_t* fphtmlgoc_name = L"htmlgoc.htm";
	fphtml_goc = _wfopen(fphtmlgoc_name, L"rt, ccs=UTF-8");		//Mo file htmlgoc.htm

	if (fpcsv != NULL)
	{
		while (1)
		{
			sinhvien sv;
			readcsv_loai1(fpcsv, sv);			// Sau khi ham nay` thuc hien, con tro dang dung cuoi hang`.
			writehtml(fphtml, fphtml_goc, sv);
			rewind(fphtml_goc);
			char ch = fgetwc(fpcsv);	// Sau khi fgetc, ch= ky tu xuong dong`=10(ASCII)  va`con tro se chuyen xuong dong ke tiep (neu co) . 
			// Nguoc lai (neu khong co dong ke tiep) thi` fgetc se duoc ch= ky tu ket thuc= -1(ASCII)
			if ((int)ch == 10)			// Ky tu xuong dong
				continue;
			else
				if ((int)ch == -1)		// Ky tu ket thuc tap tin
					break;
		}
	}
	else
		return;

	fclose(fpcsv);
	fclose(fphtml);
	fclose(fphtml_goc);






	/*
	wchar_t*fname_html = wcscat(sv.mssv, L".txt");
	fphtml = _wfopen(fname_html, L"wt, ccs=UTF-8");
	//wprintf(L"%ls phùng quôc việt", fname_html);

	if (fphtml != NULL)
	{
	fwprintf(fphtml, L"%ls phùng quốc việt",sv.mssv);
	*/











	/*FILE* fpin, *fpout;
	char*fname = "D:\\TESTFILE\\quocviet.txt", *fcopy="D:\\TESTFILE\\copy.txt";

	fpin = fopen(fname, "rt");
	if (fpin == NULL)
	{
	printf("khong mo duoc\n");
	return;
	}
	fpout = fopen(fcopy, "wt");
	if(fpout==NULL){
	printf("khong mo duoc\n");
	return;
	}
	transfile(fpin, fpout);
	//transfile(fpin, stdout);
	fclose(fpin);
	fclose(fpout);
	*/




}
