# frozen_string_literal: true

# class
class SlotsController < ApplicationController
  before_action :check_user, only: %i[destroy edit new]
  before_action :set_slot, only: %i[edit update show destroy]
  def new
    @slot = Slot.new
  end

  def index
    # debugger
    @slot = Slot.all
  end

  def show; end

  def edit; end

  def update
    if @slot.update(slot_params)
      flash[:notice] = 'Slot Successfully Updated'
      redirect_to @slot
    else
      render 'edit', status: :unprocessable_entity
    end
  end

  def create
    @slot = Slot.new(slot_params)
    if @slot.save
      flash[:notice] = 'Slot Successfully Created.'
      redirect_to @slot
    else
      render 'new', status: :unprocessable_entity
    end
  end

  def destroy
    @slot.destroy
    redirect_to slots_path
  end

  private

  def slot_params
    params.require(:slot).permit(:slot_number, :floor_id, :status)
  end

  def set_slot
    @slot = Slot.find(params[:id])
  rescue ActiveRecord::RecordNotFound => e
    redirect_to slots_path
    flash[:notice] = e
  end

  def check_user
    return unless current_user.admin == false

    flash[:alert] = 'You cannot open this'
    redirect_to root_path
  end
end
