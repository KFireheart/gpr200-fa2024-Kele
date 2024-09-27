#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform float _Time;
uniform bool jumpEnabled; 
uniform int useTex1;


void main()
{
    ourColor = aColor;
    vec3 pos = aPos;

    
    if (jumpEnabled) {
        pos.y += abs(sin(_Time * 3.0) * 0.2);
    }

     TexCoord = aTexCoord;

    if (useTex1 == 1) {
        
         gl_Position = vec4(pos.x * 2, pos.y * 2, pos.z * 2, 1.0);
    }
        else {
        gl_Position = vec4(pos.x / 3, pos.y / 2, pos.z, 1.0);
    }
      

   
    
}