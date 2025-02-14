// After running this program run "convert -delay 10 -loop 0 plots/frame_*.png plots/love_animation.gif" to make gif
#include <TCanvas.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TString.h>
#include <iostream>
#include <cmath>

void makegif_love() {
    TCanvas *c = new TCanvas("c", "", 800, 600);
    //c->SetGrid();
    
    int nFrames = 100; // Number of frames
    int nPoints = 100; // Number of points for the heart shape

    for (int i = 0; i < nFrames; i++) {
        double x[nPoints], y[nPoints];

        for (int j = 0; j < nPoints; j++) {
            double t = 2 * M_PI * j / nPoints;
            x[j] = 16 * pow(sin(t), 3);  // Heart equation (X)
            y[j] = 13 * cos(t) - 5 * cos(2*t) - 2 * cos(3*t) - cos(4*t); // Heart equation (Y)

            // Add animation effect: Scaling or pulsating
            double scale = 0.1 + 0.1 * sin(0.02 * i * M_PI);
            x[j] *= scale;
            y[j] *= scale;
        }

        TGraph *graph = new TGraph(nPoints, x, y);
        graph->SetTitle(" ; ; ");
        graph->SetLineColor(kRed);
        graph->SetLineWidth(8);
	graph->SetLineColor(kRed);
	graph->GetXaxis()->SetLabelSize(0);
	graph->GetYaxis()->SetLabelSize(0);
	graph->GetXaxis()->SetTickLength(0);
	graph->GetYaxis()->SetTickLength(0);
	graph->GetXaxis()->SetLimits(-5, 5);
	graph->GetYaxis()->SetRangeUser(-5, 5);
        graph->Draw("AL");

        TString filename;
        filename.Form("plots/frame_%03d.png", i);
        c->SaveAs(filename);

        delete graph; // Free memory
    }

    std::cout << "Frames saved! Now convert them to GIF using ImageMagick." << std::endl;
}


