#include <sil/sil.hpp>
#include <iostream>
#include "random.hpp"
#include <cmath>
#include <string>
#include <complex>

void keep_green_only(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
{
    color.r = 0.f ;
    color.b = 0.f ;
}
}


void channels_swap(sil::Image& image) // Prend l'image par référence pour pouvoir la modifier
{
   for (glm::vec3& color : image.pixels())
{
    std::swap(color.r,color.b) ;
}
}

void black_white(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        float moyenne {(color.r + color.b + color.g)/3.f} ;
        color.r = moyenne ;
        color.b = moyenne ;
        color.g = moyenne ;

    }
}

void negative(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        float colorR {};
        float colorB {};
        float colorG {};
        colorR = 1.f-color.r ;
        colorB = 1.f-color.b ;
        colorG = 1.f-color.g ;
        color.r=colorR ;
        color.b=colorB ;
        color.g=colorG ;
    }
}

sil::Image degrade()
{
    sil::Image image{300, 200} ;
    for (int x{0}; x < image.width(); x++)
{
    for (int y{0}; y < image.height(); y++)
    {
        float x_float {static_cast<float>(x)};
        float gris {x_float/image.width()} ;
        image.pixel( x , y) = glm::vec3{gris, gris, gris};
        
    }
}
    return image;
}


void mirror(sil::Image& image)
{
    int t {image.width()} ;
    for (int x{0}; x < image.width()/2; x++) //attention à ne parcourir que la moitié de l'image
    {
        for (int y{0}; y < image.height(); y++)
        {
            std::swap(image.pixel(x,y),image.pixel(t-(x+1),y)) ;
        }
    }
}

void noise(sil::Image& image)
{
    for (int i {0} ; i<(image.width()*image.height()/10) ; i++)
    {
        int X {random_int(0,image.width()-1)} ; //attention les colonnes vont de 0 à 299 (si width=300)
        int Y {random_int(0,image.height()-1)} ;
        
        image.pixel(X,Y) = glm::vec3{random_float(0,1), random_float(0,1), random_float(0,1)};
        
    }
    
}

sil::Image angle_droit(sil::Image const& image) 
{
    sil::Image angle{image.height(), image.width()};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            angle.pixel(image.height()-1-y, x) = image.pixel(x,y); 
        }
    }
    
    return angle ;
}

sil::Image RGB_split(sil::Image const& image) 
{
    sil::Image RGB{image.width(), image.height()};
    
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if (x<30)
            {
                for (int i {0} ; i<30 ; i++)
                {
                    RGB.pixel(x, y).b = image.pixel(x+(2*i+1), y).b ;
                    RGB.pixel(x, y).g = image.pixel(x, y).g ;
                    RGB.pixel(x, y).r = image.pixel(x, y).r ;
                }
                
            }
            else if ((image.width()-30)<=x)
            {
                for (int j {0} ; j<30; j++)
                {
                    RGB.pixel(x, y).r = image.pixel(x-(2*j+1), y).r ;
                    RGB.pixel(x, y).g = image.pixel(x, y).g ;
                    RGB.pixel(x, y).b = image.pixel(x, y).b ;
                }
            }
            else 
            {
                RGB.pixel(x, y).b = image.pixel(x+30, y).b ;
                RGB.pixel(x, y).r = image.pixel(x-30, y).r ;
                RGB.pixel(x, y).g = image.pixel(x, y).g ;
            }
        }
    }
    return RGB ;
}

void light(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        float a {0.5} ;
        float r_clair {pow(color.r,a)} ;
        color.r = r_clair;
        float b_clair {pow(color.b,a)} ;
        color.b = b_clair;
        float g_clair {pow(color.g,a)} ;
        color.g = g_clair;
        

    }
}

sil::Image disque(sil::Image const& image) 
{
    sil::Image rond{500, 500};
    int milieu {rond.width()/2} ;
    int rayon {100} ;
    for (int x{milieu-rayon}; x <= milieu+rayon ; x++)
    {
        for (int y{milieu-rayon}; y <= milieu+rayon; y++)
        {
            if ((pow((x-milieu),2)+pow(y-milieu,2))<pow(rayon,2))
            {
                rond.pixel(x, y).r = 1.f;
                rond.pixel(x, y).g = 1.f;
                rond.pixel(x, y).b = 1.f;
            }
        }
    }   
    return rond ;
}




// { //HELEANN
//     sil::Image cercle{500, 500};
//     int milieu {cercle.width()/2} ;
//     int rayon {100} ;
//     for (float x{0}; x < cercle.width(); x++)
//     {
//         for (float y{0}; y < cercle.height(); y++)
//         {
//             int rayon {100} ;
//             int thickness {rayon+10} ;
//             int cercle_nb {((x - milieu)*(x - milieu)+(y - milieu)*(y - milieu))} ;

//             if (cercle_nb <= (thickness*thickness))
//             {
//                 cercle.pixel(x, y).r = 1.f;
//                 cercle.pixel(x, y).g = 1.f;
//                 cercle.pixel(x, y).b = 1.f;
//             }
//         }
//     }
// }

//nouveau code anneau

sil::Image cercle(sil::Image const& image) 
{
    sil::Image anneau{500, 500};
    int milieu {anneau.width()/2} ;
    int rayon {100} ;
    for (int x{0}; x < anneau.width(); x++)
    {
        for (int y{0}; y < anneau.height(); y++)
        {
            //int rayon {100} ;
            int thickness {rayon+10} ;
            int cercle_nb {((x - milieu)*(x - milieu)+(y - milieu)*(y - milieu))} ;

            if (cercle_nb <= (thickness*thickness) && cercle_nb > (rayon*rayon))
            {
                anneau.pixel(x, y).r = 1.f;
                anneau.pixel(x, y).g = 1.f;
                anneau.pixel(x, y).b = 1.f;
            }
        }
    }
    return anneau ;
}

//anneau pour rosace
sil::Image cercle_rosace(sil::Image& image, int milieu_x, int milieu_y, int rayon) 
{
    //sil::Image cercle{500, 500};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            //int rayon {100} ;
            int thickness {rayon+10} ;
            int cercle_nb {((x - milieu_x)*(x - milieu_x)+(y - milieu_y)*(y - milieu_y))} ;

            if (cercle_nb <= (thickness*thickness) && cercle_nb > (rayon*rayon))
            {
                image.pixel(x, y).r = 1.f;
                image.pixel(x, y).g = 1.f;
                image.pixel(x, y).b = 1.f;
            }
        }
    }
}

// nouveau code rosace


// {
//     sil::Image cercle{500, 500}; // MOI marche
//     int milieu {cercle.width()/2} ;
//     int rayon {100} ;
//     for (int x {milieu-rayon}; x <= milieu+rayon ; x++)
//     {
//         for (int y {milieu-rayon}; y <= milieu+rayon; y++)
//         {
//             if ((pow((x-milieu),2)+pow(y-milieu,2))<pow(rayon,2))
//             {
//                 cercle.pixel(x, y).r = 1.f;
//                 cercle.pixel(x, y).g = 1.f;
//                 cercle.pixel(x, y).b = 1.f;
//             }
//         }
//     }   
//     int thickness {rayon-10} ;
//     for (int x {milieu-thickness}; x <= milieu+thickness ; x++)
//     {
//         for (int y{milieu-thickness}; y <= milieu+thickness; y++)
//         {
//             if ((pow((x-milieu),2)+pow(y-milieu,2))<pow(thickness,2))
//             {
//                 cercle.pixel(x, y).r = 0.f;
//                 cercle.pixel(x, y).g = 0.f;
//                 cercle.pixel(x, y).b = 0.f;
//             }
//         }
//     }   
//     return cercle ;
// }

sil::Image animation(int milieu_x) 
{
    sil::Image anime{500, 500};
    int milieu_y {anime.height()/2} ;
    //int milieu_x {100} ;
    int rayon {100} ;
    for (int x{milieu_x-rayon}; x <= milieu_x+rayon ; x++)
    {
        for (int y{milieu_y-rayon}; y <= milieu_y+rayon; y++)
        {
            if ((pow((x-milieu_x),2)+pow(y-milieu_y,2))<pow(rayon,2))
            {
                anime.pixel(x, y).r = 1.f;
                anime.pixel(x, y).g = 1.f;
                anime.pixel(x, y).b = 1.f;
            }
        }
    }   
    return anime ;
}


//void cercle_rosace(sil::Image& image, int milieu_x , int milieu_y, int rayon)
//{
    // for (int x {milieu_x-rayon}; x <= milieu_x+rayon ; x++)
    // {
    //     for (int y{milieu_y-rayon}; y <= milieu_y+rayon; y++)
    //     {
    //         if ((pow((x-milieu_x),2)+pow(y-milieu_y,2))<pow(rayon,2))
    //         {
    //             image.pixel(x, y).r = 1.f;
    //             image.pixel(x, y).g = 1.f;
    //             image.pixel(x, y).b = 1.f;
    //         }
    //     }
    // }   
    

 //HELEANN
    //sil::Image cercle{500, 500};
    //int milieu {image.width()/2} ;
    // for (int x{0}; x < image.width(); x++)
    // {
    //     for (int y{0}; y < image.height(); y++)
    //     {
    //         //int rayon {100} ;
    //         int thickness {rayon+10} ;
    //         int cercle_nb {((x - milieu_x)*(x - milieu_x)+(y - milieu_y)*(y - milieu_y))} ;

    //         if (cercle_nb <= (thickness*thickness) && cercle_nb > (rayon*rayon))
    //         {
    //             image.pixel(x, y).r = 1.f;
    //             image.pixel(x, y).g = 1.f;
    //             image.pixel(x, y).b = 1.f;
    //         }
    //     }
    // }

//}

sil::Image exo_rosace() 
{
    sil::Image rosace{500, 500};
    int rayon {100} ;
    cercle_rosace(rosace, rosace.width()/2, rosace.height()/2, rayon);
    for (int angle {0} ; angle<360 ; angle+=60)
    {
        int milieu_x {rayon*cos(angle)+rosace.width()/2} ;
        int milieu_y {rayon*sin(angle)+rosace.height()/2} ;
        cercle_rosace(rosace, milieu_x, milieu_y, rayon);   
    }


    return rosace;


    //         int milieu_x {(rosace.width()/2-rayon)*angle} ;
    //         int milieu_y {rosace.height()/2*angle} ;
    //         for (int x {milieu_x-rayon}; x <= milieu_x+rayon ; x++)
    //         {
    //             for (int y{milieu-rayon}; y <= milieu+rayon; y++)
    //             {
    //                 if ((pow((x-milieu),2)+pow(y-milieu,2))<pow(rayon,2))
    //                 {
    //                     rosace.pixel(x, y).r = 1.f;
    //                     rosace.pixel(x, y).g = 1.f;
    //                     rosace.pixel(x, y).b = 1.f;
    //                 }
    //             }
    //         }   
    //         int thickness {rayon-20} ;
    //         for (int x {milieu_x-thickness}; x <= milieu_x+thickness ; x++)
    //         {
    //             for (int y{milieu_y-thickness}; y <= milieu_y+thickness; y++)
    //             {
    //                 if ((pow((x-milieu_x),2)+pow(y-milieu_y,2))<pow(thickness,2))
    //                 {
    //                     rosace.pixel(x, y).r = 0.f;
    //                     rosace.pixel(x, y).g = 0.f;
    //                     rosace.pixel(x, y).b = 0.f;
    //                 }
    //             }
    //         }
    //     }
    //     int angle {60+i} ;
    //     cercle_rosace((rosace.width()/2-rayon)*angle , rosace.height()/2*angle) ;
    // }

    // for (int i {0} ; i<6 ; i++)
    // {
        
    //     int milieu_x {(rosace.width()/2-rayon)*angle} ;
    //     int milieu_y {rosace.height()/2*angle} ;
        
        
        
        
        
        
        
    //     {
    //         for (int x {new_milieu_x-rayon}; x <= new_milieu_x+rayon ; x++)
    //         {
    //             for (int y{new_milieu_y-rayon}; y <= new_milieu_y+rayon; y++)
    //             {
    //                 x=rayon*cos(angle) ;
    //                 y=rayon*sin(angle) ;
    //                 if ((pow((x-new_milieu_x),2)+pow(y-new_milieu_y,2))<pow(rayon,2))
    //                 {
    //                     rosace.pixel(x, y).r = 1.f;
    //                     rosace.pixel(x, y).g = 1.f;
    //                     rosace.pixel(x, y).b = 1.f;
    //                 }
    //             }
    //             int thickness {rayon-20} ;
    //             for (int x {new_milieu_x-thickness}; x <= new_milieu_x+thickness ; x++)
    //             {
    //                 for (int y{new_milieu_y-thickness}; y <= new_milieu_y+thickness; y++)
    //                 {
    //                     if ((pow((x-new_milieu_x),2)+pow(y-new_milieu_y,2))<pow(thickness,2))
    //                     {
    //                         rosace.pixel(x, y).r = 0.f;
    //                         rosace.pixel(x, y).g = 0.f;
    //                         rosace.pixel(x, y).b = 0.f;
    //                     }
    //                 }
    //             }
    //         }   
            
    //     }  
    // }
    
    // return rosace ;

}

sil::Image mosaique(sil::Image const& image)
{
    sil::Image mosa{image.width()*5, image.height()*5};

    for (int j {0} ; j<image.height()*5 ; j+=image.height())
    {
        for (int i {0} ; i<image.width()*5 ; i+=image.width())
        {
            for (int x{i}; x < i+image.width(); x++)
            {
                for (int y{j}; y < j+image.height(); y++)
                {
                    mosa.pixel(x, y) = image.pixel(x%image.width(),y%image.height()) ;
                }
            }
        }
    
    }
    return mosa ;
}

void glitch(sil::Image& image)
{
    for (int i {0} ; i<100 ; i++)
    {
        int x {random_int(1,image.width()-1)} ;
        int y {random_int(0,image.height()-1)} ;
            
        int X {random_int(1,image.width()-1)} ; //attention les colonnes vont de 0 à 299 (si width=300)
        int Y {random_int(0,image.height()-1)} ;
        std::swap(image.pixel(x,y),image.pixel(X,Y)) ;
        std::swap(image.pixel(x-1,y),image.pixel(X-1,Y)) ;
        std::swap(image.pixel(x+1,y),image.pixel(X+1,Y)) ;

        int x_2 {random_int(2,image.width()-1)} ;
        int y_2 {random_int(1,image.height()-1)} ;
            
        int X_2 {random_int(2,image.width()-1)} ; 
        int Y_2 {random_int(1,image.height()-1)} ;
        std::swap(image.pixel(x_2,y_2),image.pixel(X_2,Y_2)) ;
        std::swap(image.pixel(x_2-1,y_2),image.pixel(X_2-1,Y_2)) ;
        std::swap(image.pixel(x_2+1,y_2),image.pixel(X_2+1,Y_2)) ;
        std::swap(image.pixel(x_2-1,y_2-1),image.pixel(X_2-1,Y_2-1)) ;
        std::swap(image.pixel(x_2+1,y_2-1),image.pixel(X_2+1,Y_2-1)) ;
        std::swap(image.pixel(x_2,y_2-1),image.pixel(X_2,Y_2-1)) ;
        std::swap(image.pixel(x_2+2,y_2),image.pixel(X_2+2,Y_2)) ;
        std::swap(image.pixel(x_2+2,y_2-1),image.pixel(X_2+2,Y_2-1)) ;
        int compteur {0} ;
        compteur +=i ;
    }
    
}

void mirror_mosa(sil::Image& image) //horizontal, pas utile finalement
{
    int t {image.width()} ;
    for (int x{0}; x < image.width()/2; x++) //attention à ne parcourir que la moitié de l'image
    {
        for (int y{0}; y < image.height(); y++)
        {
            std::swap(image.pixel(x,y),image.pixel(t-(x+1),y)) ;
        }
    }
}

void mirror_mosa_2(sil::Image& image) //vertical, pas utile finalement
{
    int t {image.height()} ;
    for (int x{0}; x < image.width(); x++) //attention à ne parcourir que la moitié de l'image
    {
        for (int y{0}; y < image.height()/2; y++)
        {
            std::swap(image.pixel(x,y),image.pixel(x,t-(y+1))) ;
        }
    }
}

sil::Image mosa_miroir(sil::Image const& image)
{
    sil::Image mosa_mir{image.width()*5, image.height()*5};
    for (int i {0} ; i<5 ; i++)
    {
        for (int j {0} ;  j<5 ; j++)
        {
            for (int x{0}; x < image.width(); x++) //miroir horizontal
            {
                for (int y{0}; y < image.height(); y++)
                {
                    if(i%2==0 && j%2==0)
                    {
                        mosa_mir.pixel(x+image.width()*i, y+image.height()*j) = image.pixel(x, y) ;
                    }
                    else if (i%2!=0 && j%2==0)
                    {
                        mosa_mir.pixel(x+image.width()*i, y+image.height()*j)=image.pixel(image.width()-(x+1),y) ;
                    }
                    else if (i%2==0 & j%2!=0)
                    {
                        mosa_mir.pixel(x+image.width()*i, y+image.height()*j)=image.pixel(x,image.height()-(y+1)) ;
                    }
                    else
                    {
                        mosa_mir.pixel(x+image.width()*i, y+image.height()*j)=image.pixel(image.width()-(x+1),image.height()-(y+1)) ;
                    }    
                }
            }   
            
        }

    }
            // for (int x{0}; x < image.width()*5; x=+image.width())
            // {
            //     for (int y{0}; y < image.height()*5; y=+image.height())
            //     {
            //         mosa_mir.pixel(x, y)=mosa_mir.pixel(x%image.width(),y%image.height()) ;
            //     }
            // }

        // }
    
    // }
    return mosa_mir ;
}

// void normalisation(sil::Image& image)
// {
//     for (int x{0}; x < image.width(); x++)
//     {
//         for (int y{0}; y < image.height(); y++)
//         {
//             image.pixel(x, y).r = 0.f;
//         }
//     }
// }

// void fractale_f(sil::Image& image)
// {
//     // for (int c {0} ; c<100 ; c++)
//     // {
//     //     int z {0} ;
//     //     z=z*z+c ;
//     // }
//     for (int x{0}; x < image.width(); x++)
//     {
//         for (int y{0}; y < image.height(); y++)
//         {
//             int c {0} ;
//             // c=image.pixel(x, y) ;
//         }
//     }
// }


int main()
{
    {
        sil::Image image{"images/logo.png"}; // Lis l'image
        keep_green_only(image); // Utilise la fonction pour modifier l'image
        image.save("output/keep_green_only.png"); // Sauvegarde l'image
    }
     
    {
        sil::Image image{"images/logo.png"}; // Lis l'image
        channels_swap(image); // Utilise la fonction pour modifier l'image
        image.save("output/channels_swap.png"); // Sauvegarde l'image
    }

    {
        sil::Image image{"images/logo.png"}; // Lis l'image
        black_white(image); // Utilise la fonction pour modifier l'image
        image.save("output/black_white.png"); // Sauvegarde l'image
    }

    {
        sil::Image image{"images/logo.png"}; // Lis l'image
        negative(image); // Utilise la fonction pour modifier l'image
        image.save("output/negative.png"); // Sauvegarde l'image
    }

    {
        sil::Image image{degrade()}; // Utilise la fonction pour modifier l'image
        image.save("output/degrade.png"); // Sauvegarde l'image
    }

    {
        sil::Image image{"images/logo.png"}; // Lis l'image
        mirror(image); // Utilise la fonction pour modifier l'image
        image.save("output/mirror.png"); // Sauvegarde l'image
    }

    {
        sil::Image image{"images/logo.png"}; // Lis l'image
        noise(image); // Utilise la fonction pour modifier l'image
        image.save("output/noise.png"); // Sauvegarde l'image
    }

    {
        sil::Image image{"images/logo.png"};
        angle_droit(image).save("output/angle.png");
      
    }

    {
        sil::Image image{"images/logo.png"};
        RGB_split(image).save("output/RGB.png");
      
    }

    {
        sil::Image image{"images/photo.jpg"}; // Lis l'image
        light(image); // Utilise la fonction pour modifier l'image
        image.save("output/light.jpg"); // Sauvegarde l'image
    }

    {
        sil::Image image{"images/logo.png"};
        disque(image).save("output/rond.png");
    }

    {
        sil::Image image{"images/logo.png"};
        cercle(image).save("output/anneau.png");
    }
    

    for (int i {0} ; i < 300 ; i+=5) // 300 car : anime.width()-2*rayon=500-2*100=300
    {
        sil::Image shot { animation(100+i) } ;
        std::string images { "output/anime_" + std::to_string(i) + ".png" } ;
        shot.save(images) ;
    }

    // {
    //     sil::Image noire(500, 500)
    //     cercle_rosace(noire, noire.width()/2, noire.height()/2).save("output/rosace_new.png");
    // }

    {
        sil::Image image{"images/logo.png"};
        mosaique(image).save("output/mosa.png");
    }

    {
        sil::Image image{"images/logo.png"};
        mosa_miroir(image).save("output/mosa_mir.png");
    }

    {
        sil::Image image{"images/logo.png"}; // Lis l'image
        glitch(image); // Utilise la fonction pour modifier l'image
        image.save("output/glitch.png"); // Sauvegarde l'image
    }
    
}