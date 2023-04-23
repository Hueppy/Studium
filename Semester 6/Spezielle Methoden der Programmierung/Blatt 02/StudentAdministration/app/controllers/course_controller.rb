class CourseController < ApplicationController
  def index
    @courses = Course.all
  end

  def new
    @course = Course.new
  end

  def create
    @course = Course.new course_params

    if @course.save
      redirect_to course_index_path
    else
      render :new, status: :unprocessable_entity
    end
  end

  def destroy
    @course = Course.find(params[:id])
    @course.destroy

    redirect_to course_index_path, status: :see_other
  end

  def course_lecturer(lecturer_id)
    Lecturer.find(lecturer_id)
  end

  private def course_params
    params.require(:course).permit(:title, :description, :lecturer_id)
  end
end
