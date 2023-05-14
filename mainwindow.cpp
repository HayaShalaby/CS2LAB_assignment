#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <random>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <QMessageBox>
#include <chrono>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Dataset_button_clicked()
{   if(ui->Dataset_setting->toPlainText() == "")
       ui->status_edit->setText("No dataset size entered.");
    else{
        ui->array_display->setText("");
        srand(time(NULL));
        size = (ui->Dataset_setting->toPlainText()).toInt();

        for(int i = 0; i<size; i++){
            nums[i]= rand()%1000+1;
        }

        for(int i = 0; i<size; i++){
            if(i == 0)
              ui->array_display->setText(QString::number(nums[i]));
            else
                ui->array_display->setText(ui->array_display->toPlainText()+"\n"+QString::number(nums[i]));
        }

        ui-> status_edit->setText("The Dataset size: " +QString::number(size));
    }
}


void MainWindow::on_Normal_button_clicked()
{
    bool found =false;
    int count=0;
    if (ui->Find_enter->toPlainText()==""){
        ui->status_edit->setText(ui->status_edit->toPlainText()+'\n'+"Please enter a number to find");
    }
    else
    {
        ui->status_edit->setText(ui->status_edit->toPlainText()+'\n'+"Using normal search...");

        chrono::steady_clock::time_point now = chrono::steady_clock::now();

        while ( found == false && count<size)
        {
            if(nums[count]==(ui->Find_enter->toPlainText()).toInt()){
                found = true;
                indexfound=QString::number(count);
            }
            count ++;
        }

        chrono::steady_clock::time_point then = chrono::steady_clock::now();
        this->searchTime = chrono::duration_cast<chrono::nanoseconds>(then - now).count();
   }
}


void MainWindow::on_Binary_button_clicked()
{
    int l,r;
    l = 0;
    r = size-1;

    QString x= ui->Find_enter->toPlainText();

    if (x==""){
        ui->status_edit->setText(ui->status_edit->toPlainText()+'\n'+"Please enter a number to find");
    }
    else{
        ui->status_edit->setText(ui->status_edit->toPlainText()+'\n'+"Using binary search...");
        chrono::steady_clock::time_point now = chrono::steady_clock::now();
        while (l <= r) {
                int m = l + (r - l) / 2;
                if (nums[m] == x.toInt())
                {
                    indexfound=QString::number(m);
                }

                if (nums[m] < x.toInt())
                    l = m + 1;
                else
                    r = m - 1;
            }
        chrono::steady_clock::time_point then = chrono::steady_clock::now();
        this->searchTime = chrono::duration_cast<chrono::nanoseconds>(then - now).count();
    }
}


void MainWindow::on_Find_button_clicked()
{
    if (indexfound==""){
        ui->status_edit->setText(ui->status_edit->toPlainText()+'\n'+"The number was not found OR no search was chosen.");
    }
    else {
        ui->status_edit->setText(ui->status_edit->toPlainText()+'\n'+"The number is at position " + indexfound + " in the array.");
        //QMessageBox *msgBox = new QMessageBox(QMessageBox::Information, "Search & Sort", "Search Time: " + QString::number(searchTime) + " nanoseconds" + "    " + "Sort Time: " + QString::number(sortTime) + " nanoseconds");
        //    ui->verticalLayout->addWidget(msgBox);
    }
}


void MainWindow::on_STL_button_clicked()
{
    if(ui->array_display->toPlainText() == "")
      ui->status_edit->setText(ui->status_edit->toPlainText()+'\n'+"There is no array to sort.");
    else{
        ui->array_display->setText("");

         chrono::steady_clock::time_point now = chrono::steady_clock::now();

        sort(nums , nums + size );

         chrono::steady_clock::time_point then = chrono::steady_clock::now();
         this->sortTime = chrono::duration_cast<chrono::nanoseconds>(then - now).count();

        for(int i = 0; i<size; i++){
            if(i == 0)
              ui->array_display->setText(QString::number(nums[i]));
            else
                ui->array_display->setText(ui->array_display->toPlainText()+"\n"+QString::number(nums[i]));
        }
        ui->arrayState_label->setText("Sorted array");
        ui->status_edit->setText(ui->status_edit->toPlainText()+'\n'+"Sorted using STL sort.");
    }
}



// Merge two subarrays L and M into nums
void merge(int nums[], int p, int q, int r) {

  // Create L ← A[p..q] and M ← A[q+1..r]
  int n1 = q - p + 1;
  int n2 = r - q;

  int L[n1], M[n2];

  for (int i = 0; i < n1; i++)
    L[i] = nums[p + i];
  for (int j = 0; j < n2; j++)
    M[j] = nums[q + 1 + j];

  // Maintain current index of sub-arrays and main array
  int i, j, k;
  i = 0;
  j = 0;
  k = p;

  // Until we reach either end of either L or M, pick larger among
  // elements L and M and place them in the correct position at A[p..r]
  while (i < n1 && j < n2) {
    if (L[i] <= M[j]) {
      nums[k] = L[i];
      i++;
    } else {
      nums[k] = M[j];
      j++;
    }
    k++;
  }

  // When we run out of elements in either L or M,
  // pick up the remaining elements and put in A[p..r]
  while (i < n1) {
    nums[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    nums[k] = M[j];
    j++;
    k++;
  }
}

// Divide the array into two subarrays, sort them and merge them
void mergeSort(int nums[], int l, int r) {
  if (l < r) {
    // m is the point where the array is divided into two subarrays
    int m = l + (r - l) / 2;

    mergeSort(nums, l, m);
    mergeSort(nums, m + 1, r);

    // Merge the sorted subarrays
    merge(nums, l, m, r);
  }
}
void MainWindow::on_Merge_button_clicked()
{   if(ui->array_display->toPlainText() == "")
        ui->status_edit->setText(ui->status_edit->toPlainText()+'\n'+"There is no array to sort.");
    else{
        ui->array_display->setText("");

         int  l = 0;
         int  r = size - 1;

         chrono::steady_clock::time_point now = chrono::steady_clock::now();

        mergeSort(nums, l, r);

        chrono::steady_clock::time_point then = chrono::steady_clock::now();
        this->sortTime = chrono::duration_cast<chrono::nanoseconds>(then - now).count();

        for(int i = 0; i<size; i++){
            if(i == 0)
              ui->array_display->setText(QString::number(nums[i]));
            else
                ui->array_display->setText(ui->array_display->toPlainText()+"\n"+QString::number(nums[i]));
        }
        ui->arrayState_label->setText("Sorted array");
        ui->status_edit->setText(ui->status_edit->toPlainText()+'\n'+"Sorted using Merge Sort.");
    }
}

