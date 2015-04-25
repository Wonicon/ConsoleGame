#include "console.h"
#include <Windows.h>
#include <assert.h>

SMALL_RECT windowSize = { 0, 0, WIDTH - 1, HEIGHT - 1 };
COORD bufferSize = { WIDTH, HEIGHT };
COORD charBufferSize = { WIDTH, HEIGHT };
COORD InitPos = { 0, 0 };

static HANDLE hStdin;                  // 控制台输入句柄
static HANDLE hStdout;                 // 控制台输出句柄
static HWND   hWin;                    // 窗口句柄
static CHAR   screen[HEIGHT * WIDTH];  // 屏幕字符缓冲区

void InitConsole(void)
{
	// 获得句柄
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	hWin = GetForegroundWindow();
	// 控制台光标设置为不可见
	CONSOLE_CURSOR_INFO info = { 1, 0 };
	SetConsoleCursorInfo(hStdout, &info);

	SetConsoleScreenBufferSize(hStdout, bufferSize);
	SetConsoleTitleA(TITLE);
	SetConsoleWindowInfo(hStdout, TRUE, &windowSize);
}
// 检测当前窗口是否激活
bool IsWindowActive(void)
{
	return hWin == GetForegroundWindow();
}
// 重绘缓冲区
void RedrawConsole(void)
{
	DWORD rst;
	static COORD P = { 0, 0 };
	SetConsoleCursorPosition(hStdout, P);
	WriteConsoleA(hStdout, screen, HEIGHT * WIDTH - 1, &rst, NULL);
	//assert(rst == HEIGHT * WIDTH);
}
// 写入缓冲区
void WriteChar(int x, int y, CHAR ch)
{
	screen[x + y * WIDTH] = ch;
}
// 绘制字符串
void WriteString(int x, int y, CHAR str[])
{
	int index = x + y * WIDTH;
	memcpy(screen + index, str, strlen(str));
}
// 绘制竖线
void WriteColumn(int x, int y, CHAR str[])
{
	int index = x + y * WIDTH;
	int len = strlen(str);
	for (int i = 0; i < len; i++) {
		screen[index] = *str++;
		index += WIDTH;
	}
}
// 绘制矩形
void WriteBlock(int x, int y, int height, int width, CHAR str[])
{
	int index = x + y * WIDTH;
	int i = 0;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (str[i] != JMP_CHAR) {
				screen[index + x] = str[i];
			}
			i++;
		}
		index += WIDTH;
	}
}
// 清空缓冲区
void ClearConsoleBuffer(void)
{
	memset(screen, 0, WIDTH * HEIGHT);
}

