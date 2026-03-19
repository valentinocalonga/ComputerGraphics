/**
 * @file		S02_BasicRasterization.cpp
 * @brief	Basic rasterization using GLM
 *
 * @author	Valentino Calonga - SUPSI [valentino.calonga@student.supsi.ch]
 */



 //////////////
 // #INCLUDE //
 //////////////

    // 3D math:   
#define GLM_ENABLE_EXPERIMENTAL     // Required by glm/gtx/string_cast.hpp
#include <glm/glm.hpp>              // Add path to required header files under "Project->Properties->C/C++->General->Additional Include Directories"
#include <glm/gtx/string_cast.hpp>  // For glm::to_string

#include <glm/gtc/matrix_transform.hpp> // For deprecated OpenGL matrix transformations

// C++ libs:
#include <iostream>
using namespace std;

///////////////
// FUNCTIONS //
///////////////

// Convert clip coordinates to normalized devices coordinates NDC
glm::vec3 clipToNdc(glm::vec4 v)
{
   return glm::vec3(v.x / v.w, v.y / v.w, v.z / v.w);
}

// Convert NDC to screen coordinates for a 100x100 display
glm::vec3 ndcToScreen(glm::vec3 v)
{
   float x_sc = (v.x + 1.0f) * 100.0f / 2.0f;
   float y_sc = (v.y + 1.0f) * 100.0f / 2.0f;
   float z_sc = (v.z + 1.0f) / 2.0f;

   return glm::vec3(x_sc, y_sc, z_sc);
}


//////////
// MAIN //
//////////

/**
 * Application entry point.
 * @param argc number of command-line arguments passed
 * @param argv array containing up to argc passed arguments
 * @return error code (0 on success, error code otherwise)
 */
int main(int argc, char* argv[])
{
   // Credits:
   cout << "Basic rasterization using GLM, V. Calonga - SUPSI" << endl;
   cout << endl;
   cout << "Using GLM v"
      << GLM_VERSION_MAJOR << "."
      << GLM_VERSION_MINOR << "."
      << GLM_VERSION_PATCH << endl;

   // Declare vertices
   cout << "\n-------------------- Vertices --------------------" << endl;
   glm::vec3 a(-15.0f, 0.0f, -50.0f);
   glm::vec3 b(15.0f, 0.0f, 50.0f);
   glm::vec3 c(0.0f, 15.0f, -50.0f);

   cout << "a = " << glm::to_string(a) << endl;
   cout << "b = " << glm::to_string(b) << endl;
   cout << "c = " << glm::to_string(c) << endl;

   /*
   * a) Consider the following transformations:
   *      1) T1 = isotropic scaling by a factor of 0.5
   *      2) T2 = rotation by 90° around Z-axis
   *      3) T3 = translation by 10 units along the X-axis
   *      4) Apply these transformations in sequence: first T1, then T2, followed by T3.
   *
   *     Compute and print the world coordinates of the triangle for each case.
   */


   // Declare transformation matrices
   cout << "\n-------------------- Matrices --------------------" << endl;
   glm::mat4 T1 = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));
   glm::mat4 T2 = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
   glm::mat4 T3 = glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 0.0f, 0.0f));

   cout << "T1 = " << glm::to_string(T1) << endl;
   cout << "T2 = " << glm::to_string(T2) << endl;
   cout << "T3 = " << glm::to_string(T3) << endl;

   // Case 1: T1
   cout << "\n-------------------- Case 1: T1 --------------------" << endl;
   glm::vec4 a1 = T1 * glm::vec4(a, 1.0f);
   glm::vec4 b1 = T1 * glm::vec4(b, 1.0f);
   glm::vec4 c1 = T1 * glm::vec4(c, 1.0f);

   cout << "a1 = " << glm::to_string(a1) << endl;
   cout << "b1 = " << glm::to_string(b1) << endl;
   cout << "c1 = " << glm::to_string(c1) << endl;

   // Case 2: T2 * T1
   cout << "\n-------------------- Case 2: T2 * T1 --------------------" << endl;
   glm::mat4 M2 = T2 * T1;
   glm::vec4 a2 = M2 * glm::vec4(a, 1.0f);
   glm::vec4 b2 = M2 * glm::vec4(b, 1.0f);
   glm::vec4 c2 = M2 * glm::vec4(c, 1.0f);

   cout << "a2 = " << glm::to_string(a2) << endl;
   cout << "b2 = " << glm::to_string(b2) << endl;
   cout << "c2 = " << glm::to_string(c2) << endl;

   // Case 3: T3 * T2 * T1
   cout << "\n-------------------- Case 3: T3 * T2 * T1 --------------------" << endl;
   glm::mat4 M3 = T3 * T2 * T1;
   glm::vec4 a3 = M3 * glm::vec4(a, 1.0f);
   glm::vec4 b3 = M3 * glm::vec4(b, 1.0f);
   glm::vec4 c3 = M3 * glm::vec4(c, 1.0f);

   cout << "a3 = " << glm::to_string(a3) << endl;
   cout << "b3 = " << glm::to_string(b3) << endl;
   cout << "c3 = " << glm::to_string(c3) << endl;

   /*
   * b) Repeat a) but this time compute and print the clip coordinates of the triangle after applying a perspective projection matrix with
   *    a field of view of 45°, an aspect-ratio of 1, near plane at 1, and far plane at 100 units.
   *    Assume the camera is already positioned at the origin.
   */

   cout << "\n-------------------- Perspective Projection --------------------" << endl;
   glm::mat4 P = glm::perspective(glm::radians(45.0f), 1.0f, 1.0f, 100.0f);
   cout << "P = " << glm::to_string(P) << endl;

   // Case 1: clip coordinates after T1
   cout << "\n-------------------- Case 1 clip: P * T1 --------------------" << endl;
   glm::vec4 a1_clip = P * a1;
   glm::vec4 b1_clip = P * b1;
   glm::vec4 c1_clip = P * c1;

   cout << "a1_clip = " << glm::to_string(a1_clip) << endl;
   cout << "b1_clip = " << glm::to_string(b1_clip) << endl;
   cout << "c1_clip = " << glm::to_string(c1_clip) << endl;

   // Case 2: clip coordinates after T2 * T1
   cout << "\n-------------------- Case 2 clip: P * T2 * T1 --------------------" << endl;
   glm::vec4 a2_clip = P * a2;
   glm::vec4 b2_clip = P * b2;
   glm::vec4 c2_clip = P * c2;

   cout << "a2_clip = " << glm::to_string(a2_clip) << endl;
   cout << "b2_clip = " << glm::to_string(b2_clip) << endl;
   cout << "c2_clip = " << glm::to_string(c2_clip) << endl;

   // Case 3: clip coordinates after T3 * T2 * T1
   cout << "\n-------------------- Case 3 clip: P * T3 * T2 * T1 --------------------" << endl;
   glm::vec4 a3_clip = P * a3;
   glm::vec4 b3_clip = P * b3;
   glm::vec4 c3_clip = P * c3;

   cout << "a3_clip = " << glm::to_string(a3_clip) << endl;
   cout << "b3_clip = " << glm::to_string(b3_clip) << endl;
   cout << "c3_clip = " << glm::to_string(c3_clip) << endl;

   /*
   * c) Repeat b) by computing and printing the screen coordinates of the triangle, assuming a square display with a resolution of 100x100 pixels.
   */

   cout << endl;
   cout << "\n-------------------- Screen Coordinates 100x100px --------------------" << endl;

   // Case 1
   cout << endl;
   cout << " Case 1:" << endl;

   glm::vec3 a1_ndc = clipToNdc(a1_clip);
   glm::vec3 b1_ndc = clipToNdc(b1_clip);
   glm::vec3 c1_ndc = clipToNdc(c1_clip);

   glm::vec3 a1_screen = ndcToScreen(a1_ndc);
   glm::vec3 b1_screen = ndcToScreen(b1_ndc);
   glm::vec3 c1_screen = ndcToScreen(c1_ndc);

   cout << "  a1_screen = " << glm::to_string(a1_screen) << endl;
   cout << "  b1_screen = " << glm::to_string(b1_screen) << endl;
   cout << "  c1_screen = " << glm::to_string(c1_screen) << endl;

   // Case 2
   cout << endl;
   cout << " Case 2:" << endl;

   glm::vec3 a2_ndc = clipToNdc(a2_clip);
   glm::vec3 b2_ndc = clipToNdc(b2_clip);
   glm::vec3 c2_ndc = clipToNdc(c2_clip);

   glm::vec3 a2_screen = ndcToScreen(a2_ndc);
   glm::vec3 b2_screen = ndcToScreen(b2_ndc);
   glm::vec3 c2_screen = ndcToScreen(c2_ndc);

   cout << "  a2_screen = " << glm::to_string(a2_screen) << endl;
   cout << "  b2_screen = " << glm::to_string(b2_screen) << endl;
   cout << "  c2_screen = " << glm::to_string(c2_screen) << endl;

   // Case 3
   cout << endl;
   cout << " Case 3:" << endl;

   glm::vec3 a3_ndc = clipToNdc(a3_clip);
   glm::vec3 b3_ndc = clipToNdc(b3_clip);
   glm::vec3 c3_ndc = clipToNdc(c3_clip);

   glm::vec3 a3_screen = ndcToScreen(a3_ndc);
   glm::vec3 b3_screen = ndcToScreen(b3_ndc);
   glm::vec3 c3_screen = ndcToScreen(c3_ndc);

   cout << "  a3_screen = " << glm::to_string(a3_screen) << endl;
   cout << "  b3_screen = " << glm::to_string(b3_screen) << endl;
   cout << "  c3_screen = " << glm::to_string(c3_screen) << endl;

   // Done:
   return EXIT_SUCCESS;
}