#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdlib.h>
#pragma warning(disable:4996)
typedef struct
{
	wchar_t mssv[11];
	wchar_t name[31];
	wchar_t khoa[31];
	int nienkhoa;
	wchar_t ngaysinh[11];
	wchar_t linkimage[1000];
	wchar_t email[100];
	wchar_t mota[1001];
	wchar_t sothich1[101];
	wchar_t sothich2[101];
}sinhvien;
void lui(FILE*fpcsv, wchar_t ch1)		//ch1 fgetwc lấy 1 kí tự làm con trỏ dịch chuyển tới vị trí tiếp theo, hàm lui() dùng để quay ngược lại vị trí trước khi fgetwc.
{										// VD: Nếu chữ "am" sau khi fgetwc thì con trỏ dời tới chử 'm' có thể dùng hàm fseek lui về -1, nhưng chữ "âm" phải lui về -2, "ẩm" phải fseek về -3 ; do đó để tổng quát ta viết hàm lui()
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
void readcsv(FILE*fpcsv, sinhvien &sv, int &demsothich)				// mã ASCII   34 = "	44 = ,		10 = \n
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
		}
	}
	// SO THICH 2 ----------------------------------------------------------------------------------------------
	if (demsothich == 2)
	{
		ch1 = fgetwc(fpcsv);
		if (ch1 == 34)
		{
			fwscanf(fpcsv, L"%[^\"]\"", &sv.sothich2);
		}
		else
		{
			lui(fpcsv, ch1);
			fwscanf(fpcsv, L"%[^\n]", &sv.sothich2);
		}
	}
}
void writehtml(FILE* &fphtml, FILE* fphtml_goc, sinhvien sv, int demsothich, int tuychon[9])
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
				if (tuychon[0] == 0)
					fwprintf(fphtml, L"                                <li></li>\n");
				else
					fwprintf(fphtml, L"                                <li>Họ và tên: %ls</li>\n", sv.name);
			}
			else if (wcsstr(str, L"MSSV") != NULL)
			{
				if (tuychon[1] == 0)
					fwprintf(fphtml, L"                                <li></li>\n");
				else
					fwprintf(fphtml, L"                                <li>MSSV: %ls</li>\n", sv.mssv);
			}
			else if (wcsstr(str, L"Sinh viên khoa") != NULL)
			{
				if (tuychon[2] == 0)
					fwprintf(fphtml, L"                                <li></li>\n");
				else
					fwprintf(fphtml, L"                                <li>Sinh viên khoa: %ls </li>\n", sv.khoa);
			}
			else if (wcsstr(str, L"Khóa") != NULL)
			{
				if (tuychon[3] == 0)
					fwprintf(fphtml, L"                                <li></li>\n");
				else
					fwprintf(fphtml, L"                                <li>Khóa: %d </li>\n", sv.nienkhoa);
			}
			else if (wcsstr(str, L"Ngày sinh") != NULL)
			{
				if (tuychon[4] == 0)
					fwprintf(fphtml, L"                                <li></li>\n");
				else
					fwprintf(fphtml, L"                                <li>Ngày sinh: %ls</li>\n", sv.ngaysinh);
			}
			else if (wcsstr(str, L"Email:") != NULL)
			{
				if (tuychon[5] == 0)
					fwprintf(fphtml, L"                                <li></li>\n");
				else
					fwprintf(fphtml, L"                                <li>Email: %ls</li>\n", sv.email);
			}
			else if (wcsstr(str, L"Description") != NULL)
			{
				if (tuychon[8] == 0)
					fwprintf(fphtml, L"                        <div class=\"Description\">");
				else
					fwprintf(fphtml, L"                        <div class=\"Description\">%ls", sv.mota);
			}
			else if (wcsstr(str, L"Sở thích1") != NULL)
			{
				if (tuychon[6] == 0)
					fwprintf(fphtml, L"                                <li></li>\n");
				else{
					if (demsothich == 1 || demsothich == 2)
						fwprintf(fphtml, L"                                <li>%ls</li>\n", sv.sothich1);
					else if (demsothich == 0)
						fwprintf(fphtml, L"                                <li></li>\n");
				}
			}
			else if (wcsstr(str, L"Sở thích2") != NULL)
			{
				if (tuychon[7] == 0)
					fwprintf(fphtml, L"                                <li></li>\n");
				else{
					if (demsothich == 2)
						fwprintf(fphtml, L"                                <li>%ls</li>\n", sv.sothich2);
					else if (demsothich == 1 || demsothich == 0)
						fwprintf(fphtml, L"                                <li></li>\n");
				}
			}
			else
			{
				fwprintf(fphtml, L"%ls", str);
			}
			wint_t ch = fgetwc(fphtml_goc); //kiem tra da doc het hay chua, neu da doc het htmlgoc.htm thi` break; neu chua het thi doi con tro sang trai 1L(vi` khi getc con tro da~dich sang phai 1L)
			if (ch == WEOF)
				break;
			else
				fseek(fphtml_goc, -1, SEEK_CUR);
		}
	}
	fclose(fphtml);
}
void thongtinsinhvien(sinhvien sv, int demsothich, int stt)
{
	wprintf(L"Thông tin sinh viên %d", stt);
	wprintf(L"\nMSSV: %ls", sv.mssv);
	wprintf(L"\nHọ và tên: %ls", sv.name);
	wprintf(L"\nKhoa: %ls", sv.khoa);
	wprintf(L"\nNiên khóa: %d", sv.nienkhoa);
	wprintf(L"\nNgày tháng năm sinh: %ls", sv.ngaysinh);
	wprintf(L"\nLink hình ảnh cá nhân: %ls", sv.linkimage);
	wprintf(L"\nEmail: %ls", sv.email);
	wprintf(L"\nMô tả bản thân: %ls", sv.mota);
	if (demsothich == 2)
	{
		wprintf(L"\nSở thích1: %ls", sv.sothich1);
		wprintf(L"\nSở thích2: %ls", sv.sothich2);
	}
	else if (demsothich == 1)
	{
		wprintf(L"\nSở thích1: %ls", sv.sothich1);
	}
	else wprintf(L"\nKhông có sở thích");
	wprintf(L"\n\n");
}
void tuychonxuatprofilepage(FILE*fpcsv, FILE*&fphtml, FILE*fphtml_goc, int stt, int tuychon[9])
{	tt:
	int stt_output=0;
	wprintf(L"\nNhập số thứ tự sinh viên cần xuất ra profile page \nhoặc nhập 0 để xuất tất cả: ");
	do{
		scanf("%d", &stt_output);
		if (stt_output > stt || stt_output < 0)
		{
			wprintf(L"\nKhông có sinh viên này, vui lòng nhập lại: ");
		}
	} while (stt_output > stt || stt_output < 0);
	int stt_temp = 0;
	while (1)
	{
		sinhvien sv;
		int demsothich;
		readcsv(fpcsv, sv, demsothich);
		stt_temp++;
		if (stt_output == 0)
		{
			writehtml(fphtml, fphtml_goc, sv, demsothich,tuychon);
		}
		else if (stt_output == stt_temp)
		{
			writehtml(fphtml, fphtml_goc, sv, demsothich,tuychon);
			break;
		}
		rewind(fphtml_goc);
		wint_t ch = fgetwc(fpcsv);
		if (ch == 10)
			continue;
		else if (ch == WEOF)
			break;
	}
	rewind(fpcsv);
	rewind(fphtml_goc);	
	if (stt_output != 0)
	{	
		int temp;
		do{
			wprintf(L"\nNhập 1 để tiếp tục, 0 để dừng: ");
			scanf("%d", &temp);
			if (temp == 1)
			{
				goto tt;
			}
			else if (temp == 0)
			{
				wprintf(L"Hoàn tất!!!\n");
				break;
			}
			else wprintf(L"Nhập lại!!!\n");
		} while (temp != 1 && temp != 0);
	}
	else { 
		wprintf(L"Hoàn tất!!!\n"); 
	}
}

void mangdanhdautuychon(int tuychon[9])
{
	int temp;
	wprintf(L"Mặc định chương trình sẽ xuất profile với cấu hình đầy đủ\nNếu muốn chọn cấu hình theo ý mình vui lòng nhập 1, ngược lại nhập 0: ");
	scanf("%d", &temp);
	if (temp == 1){
		wprintf(L"\nNhập 1 trước thông tin muốn hiển thị / Nhập 0 trước thông tin muốn ẩn\n");
		wprintf(L"1. Họ và tên: ");
		scanf("%d", &tuychon[0]);
		wprintf(L"2. MSSV: ");
		scanf("%d", &tuychon[1]);
		wprintf(L"3. Khoa: ");
		scanf("%d", &tuychon[2]);
		wprintf(L"4. Khóa: ");
		scanf("%d", &tuychon[3]);
		wprintf(L"5. Ngày sinh: ");
		scanf("%d", &tuychon[4]);
		wprintf(L"6. Email: ");
		scanf("%d", &tuychon[5]);
		wprintf(L"7. Sở thích 1: ");
		scanf("%d", &tuychon[6]);
		wprintf(L"8. Sở thích 2: ");
		scanf("%d", &tuychon[7]);
		wprintf(L"9. Mô tả: ");
		scanf("%d", &tuychon[8]);
	}
}
void main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	FILE* fpcsv;
	FILE* fphtml;
	FILE* fphtml_goc;
	int tuychon[9] = { 1, 1, 1, 1, 1, 1, 1, 1, 1};

	wchar_t* fpcsv_name = L"danhsachsinhvien.csv";
	fpcsv = _wfopen(fpcsv_name, L"rt, ccs=UTF-8");		//Mo file CSV

	wchar_t* fphtmlgoc_name = L"origin_html.htm";
	fphtml_goc = _wfopen(fphtmlgoc_name, L"rt, ccs=UTF-8");		//Mo file htmlgoc.htm

	if (fpcsv != NULL)
	{
		int stt = 0;
		while (1)
		{
			sinhvien sv;
			int demsothich;
			readcsv(fpcsv, sv,demsothich);			// Sau khi ham nay` thuc hien, con tro dang dung cuoi hang`.
			stt++;
			thongtinsinhvien(sv, demsothich, stt);
			rewind(fphtml_goc);
			wint_t ch = fgetwc(fpcsv);	// Sau khi fgetc, ch= ky tu xuong dong`=10(ASCII)  va`con tro se chuyen xuong dong ke tiep (neu co) . 
										// Nguoc lai (neu khong co dong ke tiep) thi` fgetc se duoc ch= ky tu ket thuc= -1(ASCII) = WEOF
			if (ch == 10)				// Ky tu xuong dong
				continue;
			else if (ch == WEOF)		// Ky tu ket thuc tap tin
				break;
		}
		rewind(fpcsv);
		mangdanhdautuychon(tuychon);
		tuychonxuatprofilepage(fpcsv, fphtml, fphtml_goc, stt,tuychon);
	}
	else
		return;
	
	fclose(fpcsv);
	fclose(fphtml_goc);
	system("pause");
	
}
// Phùng Quốc Việt	MSSV: 1712907	Lớp: 17CTT7