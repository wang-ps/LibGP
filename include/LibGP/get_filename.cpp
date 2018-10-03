#include "get_filename.h"

LIBGP_INLINE bool LibGP::get_filename(std::string& filename,
    bool open, LibGP::FileType filetype, std::string default_name) {
  // file index
  static int iImg = 1, iObj = 1;

  TCHAR strFile[1024] = { 0 };
  OPENFILENAME ofn;					// common dialog box structure
  ZeroMemory(&ofn, sizeof(ofn));		// Initialize OPENFILENAME
  ofn.lStructSize = sizeof(ofn);
  ofn.hwndOwner = NULL;				//hwnd;
  ofn.lpstrFile = strFile;
  ofn.nMaxFile = 1024;
  ofn.nFilterIndex = 1;
  ofn.lpstrFileTitle = NULL;
  ofn.nMaxFileTitle = 0;
  ofn.lpstrInitialDir = NULL;
  ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

  switch (filetype) {
  case LibGP::MODEL_FILE:
    ofn.lpstrDefExt = TEXT("obj");
    ofn.lpstrFilter = TEXT("Object Files(*.obj;*.off;*.ply)\0 *.obj;*.off;*.ply\0");
    if (!open) {
      if (iObj < 10) {
        wsprintf(strFile, TEXT("OBJ-0%d"), iObj++);
      } else {
        wsprintf(strFile, TEXT("OBJ-%d"), iObj++);
      }
    }
    break;

  case LibGP::IMAGE_FILE:
    ofn.lpstrDefExt = TEXT("png");
    ofn.lpstrFilter = TEXT("Image Files(*.png)\0 *.png\0");
    if (!default_name.empty()) {
      _tcscpy_s(strFile, CA2T(default_name.c_str()));
    } else {
      if (!open) {
        if (iObj < 10) {
          wsprintf(strFile, TEXT("Img-0%d"), iImg++);
        } else {
          wsprintf(strFile, TEXT("Img-%d"), iImg++);
        }
      }
    }
    break;

  case LibGP::COLOR_FILE:
    ofn.lpstrDefExt = TEXT("color");
    ofn.lpstrFilter = TEXT("Color Files(*.color; *.txt; *.seg;)\0 *.color;*.txt;*.seg\0");
    break;

  default:
    ofn.lpstrDefExt = TEXT("files");
    ofn.lpstrFilter = TEXT("Files(*.*)\0 *.*\0");
    break;
  }

  BOOL flag = open ? GetOpenFileName(&ofn) : GetSaveFileName(&ofn);
  if (flag) {
    char file_name[1024];
    int pos = 0;
    while (strFile[pos] != '\0') {
      file_name[pos] = (char)strFile[pos];
      pos++;
    }
    file_name[pos] = 0;

    filename.assign(file_name);
    return true;
  }
  return false;

}

