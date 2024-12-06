#include "lodepng.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct myimage
{
  unsigned hauteur;
  unsigned largeur;
  unsigned char *rouge;
  unsigned char *vert;
  unsigned char *bleu;
  unsigned char *alpha;
}myimage;

myimage LireImage(char*);
void EcrireImage( myimage, char*);
void NoiretBlanc(myimage);


int main(int argc, char* argv[])
{
  char* in = argv[1];
  char* out = argv[2];
  if( in == NULL )
  {
    printf("Erreur : fichier mon_fichier.txt introuvable dans le repertoire courant\n");
    return 1;
  }

  else 
  {
  
  myimage im = LireImage(in);
  NoiretBlanc(im);
  EcrireImage(im, out);
  }
  return 0;
  
    
    
}



myimage LireImage(char * filename)
{
  myimage im;
  
  unsigned error;
  unsigned char* image;
  unsigned width, height;

  error = lodepng_decode32_file(&image, &width, &height, filename);
  if(error) printf("error %u: %s\n", error, lodepng_error_text(error));

  im.rouge = malloc(width*height*sizeof(unsigned char *));
  im.vert = malloc(width*height*sizeof(unsigned char *));
  im.bleu = malloc(width*height*sizeof(unsigned char *));
  im.alpha = malloc(width*height*sizeof(unsigned char *));
  im.hauteur = height;
  im.largeur = width;

  for (int i = 0; i < width*height; i++)
  {
    im.rouge[i] = image[4*i];
    im.vert[i] = image[4*i + 1]; 
    im.bleu[i] = image[4*i + 2];
    im.alpha[i] = image[4*i + 3];
  }
  return im;
  free(image);
}

void NoiretBlanc(myimage im)
{
  int moyenne;
  
  for(int i=0; i< im.largeur*im.hauteur; i++)
  {
    moyenne = ((int)im.rouge[i] + (int)im.vert[i] + (int)im.bleu[i])/3;
    im.rouge[i] = im.vert[i] = im.bleu[i] = (unsigned char)moyenne;
  }
}




void EcrireImage(myimage im, char* nom_fichier)
{
  unsigned hauteur = (unsigned)im.hauteur;
  unsigned largeur = (unsigned)im.largeur;
  unsigned char* image;

  image = malloc(hauteur*largeur*4*sizeof(unsigned char));

  for(int i =0 ; i < im.hauteur*im.largeur; i++)
  {
    image[4*i] = im.rouge[i];
    image[4*i + 1] = im.vert[i] ;
    image[4*i + 2] = im.bleu[i] ;
    image[4*i + 3] = im.alpha[i] ;
  }
  unsigned error = lodepng_encode32_file(nom_fichier, image, largeur, hauteur);

  if(error) printf("error %u: %s\n", error, lodepng_error_text(error));

}

/*
void EcrireImage( myimage im, char* nom_fichier)
{
  unsigned error; 
  unsigned char* image = (unsigned  char*)malloc(4*im.largeur*im.hauteur);
  unsigned char* png;
  size_t pngsize;
  
  for (int i = 0; i < im.largeur*im.hauteur; i++) 
  {
    image[4*i] = im.rouge[i];  
  unsigned largeur = (unsigned)im.largeur;
    image[4*i + 1] = im.vert[i];  
    image[4*i + 2] = im.bleu[i];    
    image[4*i + 3] = im.alpha[i];  
  }
  
  error = lodepng_encode32(&png, &pngsize, image, im.largeur, im.hauteur);
  if(!error) lodepng_save_file(png, pngsize, nom_fichier);

  if(error) printf("error %u: %s\n", error, lodepng_error_text(error));
  free(png);
 }
*/

// gcc -Wall -Wfatal-errors lodepng.c noir_et_blanc.c -o noir_et_blanc