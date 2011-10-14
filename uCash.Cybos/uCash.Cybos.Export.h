/*
 * uCash.Cybos Copyright (c) 2011 Taeyoung Park (primespace@naver.com)
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

#ifdef UCASHCYBOS_EXPORTS
#define UCASHCYBOS_API __declspec(dllexport)
#else
#define UCASHCYBOS_API __declspec(dllimport)
#endif

#import "d:\Daishin\cybosplus\cpdib.dll" rename_namespace("CpDib") named_guids	// cybosplus에 들어있는 cpdib.dll 경로
#import "d:\Daishin\cybosplus\cputil.dll" rename_namespace("CpUtil") named_guids	// cybosplus에 들어있는 cpdib.dll 경로
#import "d:\Daishin\cybosplus\cpsysdib.dll" rename_namespace("CpSysDib") exclude ("ICpField", "ICpFields", "CpField", "CpFields","ICpSys", "CpUnlock")
