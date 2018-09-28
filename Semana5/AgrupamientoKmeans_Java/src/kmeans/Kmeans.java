package kmeans;

import java.io.*;
public class Kmeans {
static int []x={14,15,14,26,28,30};
static int []y={28,29,30,45,38,53};
static int []v=new int[x.length];
static int c1,c2;
static Punto p1, p2;

public Kmeans() {
    p1=new Punto(20,30);
    p2=new Punto(30,50);     
    c1=0;
    c2=0;
}        
public static void calcularDistancia(){
        double d1, d2;
        c1=0; c2=0;
         for(short i=0;i<x.length;++i){
           d1=Math.sqrt(Math.pow(x[i]-p1.getX(),2)+Math.pow(y[i]-p1.getY(),2));
           d2=Math.sqrt(Math.pow(x[i]-p2.getX(),2)+Math.pow(y[i]-p2.getY(),2));
         //  System.out.println(d1+"\t"+d2);
        if(d1<=d2) {v[i]=1;++c1;}
            else   {v[i]=2;  ++c2;}      
        }
       //    System.out.println("\n\n"+c1+"\t"+c2);
    }


public static void actualizaPuntos(){
        double sX1=0, sY1=0,sX2=0,sY2=0;
        for(short i=0;i<x.length;i++){
            if(v[i]==1)
            {
                sX1+=Math.abs(x[i]);           
                sY1+=Math.abs(y[i]);        
            }
            else 
            {
                sX2+=Math.abs(x[i]);           
                sY2+=Math.abs(y[i]);     
            }
        }
        p1.setX((int) Math.round(sX1/c1));
        p1.setY((int) Math.round(sY1/c1));
        p2.setX((int) Math.round(sX2/c2));
        p2.setY((int) Math.round(sY2/c2));    
        //System.out.println(sX1+" "+sY1+" "+sX2+" "+sY2);
}
public static void estabilizar(){
    int vx1,vy1,vx2,vy2;
    vx1=p1.getX();
    vy1=p1.getY();
    vx2=p2.getX();
    vy2=p2.getY();    
    do{
    calcularDistancia();
    actualizaPuntos();
    }while(vx1==p1.getX()&&vy1==p1.getY()&&vx2==p2.getX()&&vy2==p2.getY());
    System.out.println("Kmeans estabilizado");
            System.out.println("x="+p1.getX()+"   y="+p1.getY());
            System.out.println("x="+p2.getX()+"   y= "+p2.getY());           

}
    public static void main(String[] args) throws FileNotFoundException{
  //  BufferedReader br=new BufferedReader(new  FileReader( new File("c://archivo.txt")));
  Kmeans obj=new Kmeans();  
        obj.estabilizar();
        
}
}
