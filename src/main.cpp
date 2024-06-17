#include <iostream>
#include <string>
#include <cstdlib>
#include <unordered_set>
#include "fpdfview.h"
#include "fpdf_doc.h"
#include "fpdf_text.h"
#include "fpdf_edit.h"

std::unordered_set<FPDF_PAGEOBJECT> used_resource;

void RemovedunusedResource(FPDF_PAGE page, FPDF_PAGEOBJECT obj)
{
	// 删除当前pdf未使用的元素(对象)
	if( FALSE == (FPDFPage_RemoveObject(page, obj)))
	{
		std::cerr << "remove fail" << std::endl;
		exit(0);
	}
	else
	{
		std::cout << "removed unused resource" << std::endl;
	}				
}

int main(int argc, char* argv[])
{
    FPDF_InitLibrary();
    std::cout << "PDFium of library can use!" << std::endl;
    // 加载pdf文件
    FPDF_DOCUMENT pdf_doc = FPDF_LoadDocument("test.pdf", NULL);
    if(pdf_doc == NULL)
    {
        std::cerr << "the pdf not exits" << std::endl;
        exit(0);
    }
    // 获取pdf文件的页数
    int page_count = FPDF_GetPageCount(pdf_doc);
    std::cout << "numbers of page = " << page_count << std::endl;
    for(int i = 0; i < page_count; i++)
    {
        // 加载当前页
        FPDF_PAGE page = FPDF_LoadPage(pdf_doc, i); 
        // 获取当前页的对象数
        int object_count = FPDFPage_CountObjects(page);
		for(int j = 0; j < object_count; j++)
		{
			// 得到当前页的当前对象
			FPDF_PAGEOBJECT obj = FPDFPage_GetObject(page, j);
			// 将obj放入集合中
			std::pair<std::unordered_set<FPDF_PAGEOBJECT>::iterator, bool> value = used_resource.insert(obj);
			if(!value.second)
			{
				// 插入失败 说明对象重复 需删除
				RemovedunusedResource(page, obj);
			}
			if(FPDF_PAGEOBJ_UNKNOWN == FPDFPageObj_GetType(obj))
			{
				RemovedunusedResource(page, obj);
			}
			else if(FPDF_PAGEOBJ_TEXT == FPDFPageObj_GetType(obj))
			{

			}
			else if(FPDF_PAGEOBJ_PATH == FPDFPageObj_GetType(obj))
			{
				
			}
			else if(FPDF_PAGEOBJ_IMAGE == FPDFPageObj_GetType(obj))
			{
				
			}
			else if(FPDF_PAGEOBJ_SHADING == FPDFPageObj_GetType(obj))
			{
				
			}
			else if(FPDF_PAGEOBJ_FORM == FPDFPageObj_GetType(obj))
			{
				
			}
		}
    }

    FPDF_DestroyLibrary();
    return 0;
}