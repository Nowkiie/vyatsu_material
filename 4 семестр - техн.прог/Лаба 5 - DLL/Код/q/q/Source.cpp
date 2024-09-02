#include "Header.h"
extern "C" void sum(int& d, int& n, int number);


static std::pair<bool, HWND> AddWindow(const std::wstring&& winClass, const std::wstring&& title,
	HWND hParentWnd, const WNDPROC callback)
{
	UnregisterClass(winClass.c_str(), GetModuleHandle(NULL));
	WNDCLASSEX wc{ sizeof(WNDCLASSEX) };
	HWND hWindow{};
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.lpfnWndProc = callback;
	wc.lpszClassName = winClass.c_str();
	wc.style = CS_VREDRAW | CS_HREDRAW;

	const auto create_window = [&hWindow, &winClass, &title, &hParentWnd]()->std::pair<bool, HWND> {
		if (hWindow = CreateWindow(winClass.c_str(), title.c_str(), WS_OVERLAPPEDWINDOW,
			250, 250, 250, 250, hParentWnd, NULL, NULL, NULL); !hWindow)
			return { false, NULL };

		ShowWindow(hWindow, SW_SHOWDEFAULT);
		UpdateWindow(hWindow);
		return { true, hWindow };

	};

	if (!RegisterClassEx(&wc))
		return create_window();

	return create_window();
}


int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, PWSTR szCmdLine, int nCmdShow)
{
	static MSG msg{};
	static HWND hwnd{}, hChildWnd{};;


	WNDCLASSEX wc{ sizeof(WNDCLASSEX) };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT
	{
		switch (uMsg)
		{
		case WM_CREATE:
		{
			MainWndAddWidjets(hWnd);
		}
		return 0;

	
		//break;

		case WM_COMMAND:
		{
			switch (wParam)
			{
			case OnButtonChoooseClick:
			{
				if (ff == true) // разрешние на откытие дочернего окна
				{
					f = 0;

				
					int k = 0;
					for (int i = 0; i < 6; i++)
					{
						for (int j = 0; j < 6; j++)
						{
							char buf[8];
							GetWindowTextA(hEdit[k], buf, 8);
							if (i >= j)
							{
								if (atoi(buf) == 0)
								{
									a[i][j] = 0;
								}
								else
								{
									a[i][j] = atoi(buf);
									a[j][i] = atoi(buf);
								};
							};
							k++;
						}
					}

					

					wchar_t buf1[8];
					int num = 0;

					for (int i = 0; i < 6; i++)
					{
					   {
							for (int j = 0; j < 6; j++)
							{
								swprintf_s(buf1, L"%d", a[i][j]);
								SetWindowText(hEdit[num], (LPCWSTR)buf1);
								num++;
							}
						}
					}

					char buf[8];
					GetWindowTextA(EditVer, buf, 8);
					con = atoi(buf);
					if (con > number)
					{
						MessageBox(0, L"Number greater than number of top!", L"df", MB_OK);
						break;
					};

					if (hChildWnd)
						DestroyWindow(hChildWnd);

					EnableWindow(hwnd, false);



					const auto [flag, hChild] = AddWindow(L"ChildClass", L"Child", hWnd, [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT
						{
							switch (uMsg)
							{
							case WM_CREATE:
							{
								ChildWndAddWidjets(hWnd);
								SetWindowText(Static2, L"");
								EnableWindow(hwnd, false);
							}
							return 0;


							case WM_COMMAND:
							{
								switch (wParam)
								{
								case OnButtonBackClick:
								{
									EnableWindow(hwnd, true);
									DestroyWindow(hChildWnd);
									if (!hChildWnd)
										MessageBox(0, L"������", L"df", MB_OK);

								}
								break;

								case OnButtonMultiplyClick:
								{
									HINSTANCE hInst;
									hInst = LoadLibrary(L"Dll2.dll");
									if (hInst != NULL)
									{
									int n;
									Clear(EditRes1);
									Clear(EditRes2);
									f = 2;
									//function(a, d, f);
									
										int(__cdecl * function)(int(&mas)[6][6], int(&d)[6], int(&flag));
										(FARPROC&)function = GetProcAddress(hInst, "function");
										int co = function(a, d, f);
										
										
									sum(*d, n, number);
									
									wchar_t buf2[16];
									int num = 0;
									
								    swprintf_s(buf2, L"%d", n);
									SetWindowText(EditRes2, buf2);

									EnableWindow(hwnd, true);
									DestroyWindow(hChildWnd);
									if (!hChildWnd)
										MessageBox(hWnd, L"������", L"df", MB_OK);
									//EnableWindow(hwnd, true);
									FreeLibrary(hInst);
									}
								}
								MessageBox(hWnd, L"Не подключена библиотека Dll2.lib", L"df", MB_OK);
								break;

								case OnButtonDivideClick:
								{
									HINSTANCE hInst;
									hInst = LoadLibrary(L"Dll2.dll");
									if (hInst != NULL)
									{
									f = 1;
									//function(a, d, f);
									
										int(__cdecl * function)(int(&mas)[6][6], int(&d)[6], int(&flag));
										(FARPROC&)function = GetProcAddress(hInst, "function");
										int co = function(a, d, f);

										


									wchar_t buf2[10];
									int k = 0;

								
												swprintf_s(buf2, L"%d", co+1);
												SetWindowText(EditRes1, buf2);
											
									

									EnableWindow(hwnd, true);
									DestroyWindow(hChildWnd);
									if (!hChildWnd)
										MessageBox(hWnd, L"������", L"df", MB_OK);
									//EnableWindow(hwnd, true);

									FreeLibrary(hInst);
									}
								}
								break;

								}
								break;
							}
							return 0;

							case WM_CLOSE:
							{
								ShowWindow(hwnd, SW_SHOWDEFAULT);

							}
							return 0;




							}
							return DefWindowProc(hWnd, uMsg, wParam, lParam);
						});
					hChildWnd = hChild;
				}
			}
			break;

			case OnButtonClearClick:
			{
				int k = 0;
				for (int i = 0; i < 6; i++)
				{
					for (int j = 0; j < 6; j++)
					{
						Clear(hEdit[k]);
						k++;
					}
				}
				
			}
			break;

			
			case OnButtonOKClick:
			{
				//UpdateWindow(hwnd);
				number = 0;
				
				char buf[8];
				GetWindowTextA(EditNum, buf, 8);
				number = atoi(buf);


				if ((number < 2) || (number > 6))
				{
					SetWindowText(StaticEr, L"ERROR!");
					ff = false;
				}
				else
				{
					ff = true;
					UpdateWindow(hwnd);
					MainWnd(hwnd);
					SetWindowText(StaticEr, NULL);

					int k = 0;
					for (int i = 0; i < 6; i++)
					{
						for (int j = 0; j < 6; j++)
						{
							if ((i >= number) || (j >= number))
							{
								ShowWindow(hEdit[k], 0);
								
							}
							else
							{
								ShowWindow(hEdit[k], 1);
							
								
							}
							k++;
						}
					}

				}

				break;
			}
			return 0;
			}
			break;

		}
		return 0;

		case WM_DESTROY:
		{
			PostQuitMessage(EXIT_SUCCESS);
		}
		return 0;
		}

		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	};
	wc.lpszClassName = L"MainClass";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc))
		return EXIT_FAILURE;

	if (hwnd = CreateWindow(wc.lpszClassName, L"Main", WS_OVERLAPPEDWINDOW,
		200, 200, 1000, 850, NULL, NULL, wc.hInstance, NULL); hwnd == INVALID_HANDLE_VALUE)
		return EXIT_FAILURE;

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return static_cast<int>(msg.wParam);
}