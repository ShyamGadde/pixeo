# Get the input image name from the command line argument
input_image=test-images/input-images/$1

# Generate the output image names based on the input image name
output_prefix=test-images/output-images/${1%.*}
mkdir -p $output_prefix

blur_output=${output_prefix}/${1%.*}-blur.bmp
grayscale_output=${output_prefix}/${1%.*}-grayscale.bmp
reflect_output=${output_prefix}/${1%.*}-reflect.bmp
sepia_output=${output_prefix}/${1%.*}-sepia.bmp
edges_output=${output_prefix}/${1%.*}-edges.bmp

# Apply filters to the input image and save the output images
./pixeo -b $input_image $blur_output
./pixeo -g $input_image $grayscale_output
./pixeo -r $input_image $reflect_output
./pixeo -s $input_image $sepia_output
./pixeo -e $input_image $edges_output
