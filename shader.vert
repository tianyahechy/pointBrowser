#version 430 core

//// 第一号位置存放vec4类型的offset，第二号位置存放vec4类型的color
//layout ( location = 0 ) in vec4 offset;
//layout ( location = 1 ) in vec4 color;

//// 将color输出到片断着色器中
//out vec4 vs_color;

void main( void )
{
    // 根据传入的ID使用不同gl_Position
    const vec4 vertices[3] = vec4[3](
                vec4( 0.25, -0.25, 0.5, 1.0 ),
                vec4( -0.25, -0.25, 0.5, 1.0 ),
                vec4( 0.25, 0.25, 0.5, 1.0 ) );
    gl_Position = vertices[gl_VertexID];// + offset;
    //vs_color = color;
}
