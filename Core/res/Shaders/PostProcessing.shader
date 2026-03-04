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
uniform sampler2D u_Depth;
uniform bool u_blackAndWhite;
uniform bool u_tint;
uniform vec4 u_tint_color;

uniform bool  u_vignette;
uniform float u_vignetteStrength=0.4; 
uniform float u_vignetteRadius=0.75;  
uniform float u_vignetteSoftness=0.35;

uniform bool  u_fog;
uniform vec4  u_fogColor;
uniform float u_fogDensity;
uniform float u_Near;
uniform float u_Far;


float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0;
    return (2.0 * u_Near * u_Far) / (u_Far + u_Near - z * (u_Far - u_Near));
}

void main()
{
    vec4 texColor=texture(u_Texture,v_uv);
    vec4 depth=texture(u_Depth,v_uv);

    vec4 finalColor=texColor;

     if (u_fog)
    {
        float depth01 = texture(u_Depth, v_uv).r;
        float dist    = LinearizeDepth(depth01); 

        float fogFactor = 1.0 - exp(-u_fogDensity * dist);
        fogFactor = clamp(fogFactor, 0.0, 1.0);

        finalColor.rgb = mix(finalColor.rgb, u_fogColor.rgb, fogFactor);
    }


    if (u_vignette)
    {
        vec2 p = v_uv - vec2(0.5);
        float d = length(p);

        float inner = u_vignetteRadius * 0.7071;
        float outer = clamp(inner + max(u_vignetteSoftness, 0.0001) * 0.7071, 0.0, 0.7071);

        float vig = smoothstep(outer, inner, d); 
        float amount = mix(1.0 - u_vignetteStrength, 1.0, vig);

        finalColor.rgb *= amount;
    }

    if(u_tint){
        finalColor+=u_tint_color;
    }
    if(u_blackAndWhite){
        float gray = 0.33 * (texColor.r + texColor.g + texColor.b);
        finalColor=vec4(gray);
    }
    FragColor = finalColor;
}