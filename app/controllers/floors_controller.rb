# frozen_string_literal: true

class FloorsController < ApplicationController
  before_action :check_user, only: %i[new edit update destroy]
  before_action :set_floor, only: %i[edit update destroy]

  def new
    @floor = Floor.new
  end

  def index
    @floor = Floor.all
  end

  def show
    # debugger
    @floor = Floor.find(params[:id]).slots
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
    @floor.destroy
    redirect_to floors_path
  end

  private

  def floor_params
    params.require(:floor).permit(:number_of_floor)
  end

  def set_floor
    @floor = Floor.find(params[:id])
  rescue ActiveRecord::RecordNotFound => e
    redirect_to floors_path
    flash[:notice] = e
  end

  def check_user
    return unless current_user.admin == false

    lash[:alert] = 'You cannot open this'
    redirect_to root_path
  end
end
