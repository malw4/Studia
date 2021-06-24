package mod;

import mod.neighbours.MonteCarlo;

import java.io.*;
import java.util.ArrayList;
import java.util.Random;

public class REcrystal {
    public static long criticalDensity = (long) 4.21584E+12;
    public double Avalue = 86710969050178.5;
    public double Bvalue = 9.41268203527779;
    public double critical;
    double ro=1;
    double roBefore;
    double[][] density;
    int height;
    int width;
    double time = 0.001;
    double pula = 1;
    double paczka=0;
    double Xd = 0;
    public double działko = 0.3;
    public double miniDziałko = 0.001;
    double sumaRo;
    int iteration = 0;
    MonteCarlo monteCarlo;
    Random rand = new Random();

    public REcrystal(int w, int h, MonteCarlo monte) {
        width = w;
        height = h;
        monteCarlo = monte;
        density = new double[height][width];
        critical=REcrystal.criticalDensity/(width*height);
    }

    public double[][] getRecrystalizedDensities() {
        uniformPoolDistribution();
        makeRandom();
        System.out.println("wykoano step" + time*1000);
        return density;
    }

    private void uniformPoolDistribution() {
        roBefore=ro;
        ro = Avalue / Bvalue + (1 - Avalue / Bvalue) * Math.exp(-Bvalue * time);
        if (time>0 && time<0.2) {
            pula = ro - roBefore;
            paczka = pula / (width * height);
            Xd = działko * paczka;
        }
        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {
                density[j][i] += Xd;
                pula -= Xd;
            }
        }
    }

    public void makeRandom() {
        Xd = miniDziałko * pula;
        while (pula > 1) {
            double P = rand.nextDouble();
            boolean mustBeEdge = (P <= 0.8);
            int X = rand.nextInt(width);
            int Y = rand.nextInt(height);
            if (monteCarlo.edges[Y][X] == mustBeEdge) {
                density[Y][X] += Xd;
                pula -= Xd;
            }
        }
    }

    public void saveToDoc(){
        for (int j=0;j<height;j++){
            for(int i=0;i<width;i++){
                sumaRo+=density[j][i];
            }
        }
    }
}