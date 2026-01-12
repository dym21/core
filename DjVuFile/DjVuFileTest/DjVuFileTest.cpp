#include "../DjVu.h"

#include <vector>
#include <string>
#include <windows.h>
#include <iostream>
#include <ctime>

#include "../../DesktopEditor/fontengine/ApplicationFonts.h"

std::vector<std::wstring> GetAllFilesInFolder(const std::wstring& wsFolder, const std::wstring& wsExt)
{
    std::vector<std::wstring> files;

    std::wstring searchPath = wsFolder + L"*." + wsExt;

    WIN32_FIND_DATA findData;
    HANDLE hFind = FindFirstFile(searchPath.c_str(), &findData);
    if (hFind != INVALID_HANDLE_VALUE)
    {
        do
        {
            if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            {
                files.push_back(findData.cFileName);
            }
        } while (FindNextFile(hFind, &findData));
        FindClose(hFind);
    }
    return files;
}

void ConvertFolderToPdf(CDjVuFile& reader, const std::wstring& folder)
{
    reader.Close();

    clock_t begin = clock();

    auto files = GetAllFilesInFolder(folder, L"djvu");
    for (size_t i = 0; i < files.size(); ++i)
    {
        std::wstring src = folder + files[i];
        std::wstring dst = src.substr(0, src.size() - 5) + L".pdf";

        if (reader.LoadFromFile(src))
        {
            reader.ConvertToPdf(dst);
            wprintf(L"%zu / %zu converted: %s\n", i + 1, files.size(), files[i].c_str());
        }
        else
        {
            wprintf(L"%zu / %zu failed: %s\n", i + 1, files.size(), files[i].c_str());
        }
    }

    double elapsed = double(clock() - begin) / CLOCKS_PER_SEC;
    printf("Elapsed: %.2f sec\n", elapsed);
}

int main()
{
    CApplicationFonts fonts;
    fonts.Initialize();

    CDjVuFile djvu(&fonts);

    ConvertFolderToPdf(djvu, L"D:/Test Files/djvu/");

    std::cin.get();
    return 0;
}
