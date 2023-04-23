class LecturerController < ApplicationController
  def index
    @course = Lecturer.all
  end

  def new
    @course = Lecturer.new
  end

  def create
    @course = Lecturer.new lecturer_params

    if @course.save
      redirect_to lecturer_index_path
    else
      render :new, status: :unprocessable_entity
    end
  end

  def destroy
    @course = Lecturer.find(params[:id])
    @course.destroy

    redirect_to lecturer_index_path, status: :see_other
  end

  private def lecturer_params
    params.require(:course).permit(:first_name, :last_name)
  end
end
