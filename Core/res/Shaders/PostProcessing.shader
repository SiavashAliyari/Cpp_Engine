#shader vertex

#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 uv;

out vec2 v_uv;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    v_uv = uv;
}


#shader fragment

#version 330 core
out vec4 FragColor;

in vec2 v_uv;
uniform sampler2D u_Texture;

void main()
{
    vec4 texColor=texture(u_Texture,v_uv);
    float gray = 0.33 * (texColor.r + texColor.g + texColor.b);
    float threshold = 0.5;
    if(gray > threshold)
    {
   
     texColor.rgb = vec3(1.0);   
    }
    else
    {
     // black
     texColor.rgb = vec3(0.0);
    }
    FragColor = texColor;
}