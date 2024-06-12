# frozen_string_literal: true

class FloorsController < ApplicationController
  before_action :check_user, only: %i[new edit update destroy]
  before_action :set_floor, only: %i[edit update destroy show]

  def new
    @floor = Floor.new
  end

  def index
    @floor = Floor.all
  end

  def show
    @floor = @floor.slots
  end

  def edit; end

  def update
    if @floor.update(floor_params)
      flash[:notice] = 'Floor changed'
      redirect_to @floor
    else
      render 'edit', status: :unprocessable_entity
    end
  end

  def create
    @floor = Floor.new(floor_params)
    if @floor.save
      flash[:notice] = 'Floor successfully created'
      redirect_to floors_path
    else
      render 'new', status: :unprocessable_entity
    end
  end

  def destroy
    if @floor.destroy
      flash[:notice] = 'Floor successfully deleted'
    else
      flash[:alert] = 'Failed to delete floor'
    end
    redirect_to floors_path
  end

  private

  def floor_params
    params.require(:floor).permit(:number_of_floor)
  end

  def set_floor
    @floor = Floor.find_by(id: params[:id])
    unless @floor
      flash[:alert] = 'Floor not found'
      redirect_to floors_path
    end
  end
end
