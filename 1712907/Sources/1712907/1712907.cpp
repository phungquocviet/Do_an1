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
	wchar_t sothich1[50];
	wchar_t sothich2[50];
}sinhvien;
void lui(FILE*fpcsv, wchar_t ch1)		//ch1 lấy 1 kí tự làm con trỏ dịch chuyển tới vị trí tiếp theo, hàm lui() dùng để quay ngược lại vị trí trước khi fgetwc.
{										// VD: Nếu chữ "am" sau khi fgetwc thi con trỏ dời tới chử 'm' có thể dùng hàm fseek lui về -1, nhưng chữ "âm" phải lui về -2, "ẩm" phải fseek về -3 ; do đó để tỏng quát ta dùng hàm lui()
	long byte = 0;
	while (1)
	{
		fseek(fpcsv, -1, SEEK_CUR);
		byte++;
		wchar_t ch2 = fgetwc(fpcsv);
		if (ch2 == ch1)
		{
			break;
		}
		else
		{
			fseek(fpcsv, -1, SEEK_CUR);
		}
	}
	fseek(fpcsv, -byte, SEEK_CUR);
}
void readcsv(FILE*fpcsv, sinhvien &sv, int &demsothich)
{
	wchar_t ch1 = fgetwc(fpcsv);
	demsothich = 0;
	//MSSV -------------------------------------------------------------------------------------------------
	if (ch1 == 34)
	{
		fwscanf(fpcsv, L"%[^\"]\",", &sv.mssv);
	}
	else
	{
		lui(fpcsv, ch1);
		fwscanf(fpcsv, L"%[^,],", &sv.mssv);
	}
	//Ho va ten -------------------------------------------------------------------------------------------------
	ch1 = fgetwc(fpcsv);
	if (ch1 == 34)
	{
		fwscanf(fpcsv, L"%[^\"]\",", &sv.name);
	}
	else
	{
		lui(fpcsv, ch1);
		fwscanf(fpcsv, L"%[^,],", &sv.name);
	}
	//Khoa -------------------------------------------------------------------------------------------------
	ch1 = fgetwc(fpcsv);
	if (ch1 == 34)
	{
		fwscanf(fpcsv, L"%[^\"]\",", &sv.khoa);
	}
	else
	{
		lui(fpcsv, ch1);
		fwscanf(fpcsv, L"%[^,],", &sv.khoa);
	}
	//Nien khoa  -------------------------------------------------------------------------------------------------
	ch1 = fgetwc(fpcsv);
	if (ch1 == 34)
	{
		fwscanf(fpcsv, L"%d\",", &sv.nienkhoa);
	}
	else
	{
		lui(fpcsv, ch1);
		fwscanf(fpcsv, L"%d,", &sv.nienkhoa);
	}

	//Ngay sinh  ---------------------------------------------------------------------------------------------
	ch1 = fgetwc(fpcsv);
	if (ch1 == 34)
	{
		fwscanf(fpcsv, L"%[^\"]\",", &sv.ngaysinh);
	}
	else
	{
		lui(fpcsv, ch1);
		fwscanf(fpcsv, L"%[^,],", &sv.ngaysinh);
	}
	//link hinh anh ca nhan  -----------------------------------------------------------------------------------
	ch1 = fgetwc(fpcsv);
	if (ch1 == 34)
	{
		fwscanf(fpcsv, L"%[^\"]\",", &sv.linkimage);
	}
	else
	{
		lui(fpcsv, ch1);
		fwscanf(fpcsv, L"%[^,],", &sv.linkimage);
	}

	//Email  -------------------------------------------------------------------------------------------------
	ch1 = fgetwc(fpcsv);
	if (ch1 == 34)
	{
		fwscanf(fpcsv, L"%[^\"]\",", &sv.email);
	}
	else
	{
		lui(fpcsv, ch1);
		fwscanf(fpcsv, L"%[^,],", &sv.email);
	}

	//MO TA --------------------------------------------------------------------------------------------------
	ch1 = fgetwc(fpcsv);
	if (ch1 == 34)
	{
		fwscanf(fpcsv, L"%[^\"]\"", &sv.mota);
		ch1 = fgetwc(fpcsv);
		if (ch1 == 44)
		{
			demsothich++;
		}
		else if (ch1 == 10)
		{
			fseek(fpcsv, -1, SEEK_CUR);
		}
		_putws(sv.mota);
	}
	else
	{
		int i;
		for (i = 0; ch1 != 44 && ch1 != 10; i++)
		{
			sv.mota[i] = ch1;
			ch1 = fgetwc(fpcsv);
			if ((wint_t)ch1 == WEOF)
			{
				i++;
				break;
			}
		}
		sv.mota[i] = L'\0';
		if (ch1 == 44)
		{
			demsothich++;
		}
		else if (ch1 == 10)
		{
			fseek(fpcsv, -1, SEEK_CUR);
		}
		_putws(sv.mota);
	}
	// SO THICH 1 --------------------------------------------------------------------------------------------------
	if (demsothich == 1)
	{
		ch1 = fgetwc(fpcsv);
		if (ch1 == 34)
		{
			fwscanf(fpcsv, L"%[^\"]\"", &sv.sothich1);
			ch1 = fgetwc(fpcsv);
			if (ch1 == 44)
			{
				demsothich++;
			}
			else if (ch1 == 10)
			{
				fseek(fpcsv, -1, SEEK_CUR);
			}
			_putws(sv.sothich1);
		}
		else
		{
			int i;
			for (i = 0; ch1 != 44 && ch1 != 10; i++)
			{
				sv.sothich1[i] = ch1;
				ch1 = fgetwc(fpcsv);
				if ((wint_t)ch1 == WEOF)
				{
					i++;
					break;
				}
			}
			sv.sothich1[i] = L'\0';
			if (ch1 == 44)
			{
				demsothich++;
			}
			else if (ch1 == 10)
			{
				fseek(fpcsv, -1, SEEK_CUR);
			}
			_putws(sv.sothich1);
		}
	}
	// SO THICH 2 ----------------------------------------------------------------------------------------------
	if (demsothich == 2)
	{
		ch1 = fgetwc(fpcsv);
		if (ch1 == 34)
		{
			fwscanf(fpcsv, L"%[^\"]\"", &sv.sothich2);
			_putws(sv.sothich2);
		}
		else
		{
			lui(fpcsv, ch1);
			fwscanf(fpcsv, L"%[^\n]", &sv.sothich2);
			_putws(sv.sothich2);
		}
	}
}
void writehtml(FILE* &fphtml, FILE* fphtml_goc, sinhvien sv, int demsothich)
{
	wchar_t name_htm[16];
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
			if (wcsstr(str, L"Personal_FullName") != NULL)
			{
				fwprintf(fphtml, L"                        <div class=\"Personal_FullName\"> %ls - %ls</div>", sv.name, sv.mssv);
			}
			else if (wcsstr(str, L"Personal_Department") != NULL)
			{
				fwprintf(fphtml, L"                        <div class=\"Personal_Department\">KHOA %ls</div>", sv.khoa);
			}
			else if (wcsstr(str, L"Personal_Phone") != NULL)
			{
				fwprintf(fphtml, L"                        <div class=\"Personal_Phone\">Email: %ls", sv.email);
			}
			else if (wcsstr(str, L"Personal_Hinhcanhan\"") != NULL)
			{
				fwprintf(fphtml, L"                        <img src=\"Images/%ls\" class=\"Personal_Hinhcanhan\" />", sv.linkimage);
			}
			else if (wcsstr(str, L"Họ và tên") != NULL)
			{
				fwprintf(fphtml, L"                                <li>Họ và tên: %ls</li>\n", sv.name);
			}
			else if (wcsstr(str, L"MSSV") != NULL)
			{
				fwprintf(fphtml, L"                                <li>MSSV: %ls</li>\n", sv.mssv);
			}
			else if (wcsstr(str, L"Sinh viên khoa") != NULL)
			{
				fwprintf(fphtml, L"                                <li>Sinh viên khoa: %ls - Khóa: %d</li>\n", sv.khoa, sv.nienkhoa);
			}
			else if (wcsstr(str, L"Ngày sinh") != NULL)
			{
				fwprintf(fphtml, L"                                <li>Ngày sinh: %ls</li>\n", sv.ngaysinh);
			}
			else if (wcsstr(str, L"Email:") != NULL)
			{
				fwprintf(fphtml, L"                                <li>Email: %ls</li>\n", sv.email);
			}
			else if (wcsstr(str, L"Description") != NULL)
			{
				fwprintf(fphtml, L"                        <div class=\"Description\">%ls", sv.mota);
			}
			else if (wcsstr(str, L"Sở thích1") != NULL)
			{
				if (demsothich == 1 || demsothich == 2)
					fwprintf(fphtml, L"                                <li>%ls</li>\n", sv.sothich1);
				else if (demsothich == 0)
					fwprintf(fphtml, L"                                <li></li>\n");
			}
			else if (wcsstr(str, L"Sở thích2") != NULL)
			{
				if (demsothich == 2)
					fwprintf(fphtml, L"                                <li>%ls</li>\n", sv.sothich2);
				else if (demsothich == 1 || demsothich == 0)
					fwprintf(fphtml, L"                                <li></li>\n");
			}
			else
			{
				fwprintf(fphtml, L"%ls", str);
			}
			wint_t ch = fgetwc(fphtml_goc);//kiem tra da doc het hay chua, neu da doc het htmlgoc.htm thi` break; neu chua het thi doi con tro sang trai 1L(vi` khi getc con tro da~dich sang phai 1L)
			if (ch == WEOF)
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
			int demsothich;
			readcsv(fpcsv, sv,demsothich);			// Sau khi ham nay` thuc hien, con tro dang dung cuoi hang`.
			writehtml(fphtml, fphtml_goc, sv, demsothich);
			rewind(fphtml_goc);
			wint_t ch = fgetwc(fpcsv);	// Sau khi fgetc, ch= ky tu xuong dong`=10(ASCII)  va`con tro se chuyen xuong dong ke tiep (neu co) . 
										// Nguoc lai (neu khong co dong ke tiep) thi` fgetc se duoc ch= ky tu ket thuc= -1(ASCII)
			if (ch == 10)			// Ky tu xuong dong
				continue;
			else if (ch == WEOF)		// Ky tu ket thuc tap tin
				break;
		}
	}
	else
		return;

	fclose(fpcsv);
	fclose(fphtml);
	fclose(fphtml_goc);
}
