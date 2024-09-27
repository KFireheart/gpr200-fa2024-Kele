#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D tex1;
uniform sampler2D tex2;

uniform int useTex2;
uniform float _Time;



void main()
{
   if (useTex2 == 1) {
        FragColor = texture(tex2, TexCoord);   // Use tex2 
    } else {
        FragColor = texture(tex1, vec2(TexCoord.x * 8 + _Time, TexCoord.y * 8) );  // Use tex1 
    }

}
