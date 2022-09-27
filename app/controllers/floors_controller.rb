class FloorsController < ApplicationController
  before_action :set_floor, only: [:edit, :update, :show, :destroy]
  def new
    @floor=Floor.new
end
def index
    @floor=Floor.all
end

def show
end

def edit
end

def update
    if @floor.update(floor_params)
      flash[:notice] = "Floor changed"
      redirect_to @floor
    else
      render 'edit',status: :unprocessable_entity
    end
  end
  

def create
     @floor= Floor.new(floor_params)
    if @floor.save
        flash[:notice] = "floor detail successfully filled."
        redirect_to @floor
    else
        render 'new', status: :unprocessable_entity
    end
end

def destroy
  @floor.destroy
  redirect_to floors_path
end 


def floor_params
  params.require(:floor).permit(:number_of_floor)
end

def set_floor
  @floor = Floor.find(params[:id])

rescue ActiveRecord::RecordNotFound => error
redirect_to floors_path
flash[:notice] = error
end
end
