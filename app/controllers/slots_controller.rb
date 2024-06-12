# frozen_string_literal: true

class SlotsController < ApplicationController
  before_action :check_user, only: %i[destroy edit new]
  before_action :set_slot, only: %i[edit update show destroy]

  def new
    @slot = Slot.new
  end

  def index
    @slot = Slot.all
  end

  def show; end

  def edit; end

  def update
    result = Slots::UpdateSlotService.new(@slot, slot_params).call
    if result[:success]
      flash[:notice] = 'Slot Successfully Updated'
      redirect_to @slot
    else
      flash[:alert] = result[:errors].full_messages.join(', ')
      render 'edit', status: :unprocessable_entity
    end
  end

  def create
    result = Slots::CreateSlotService.new(slot_params).call
    if result[:success]
      flash[:notice] = 'Slot Successfully Created.'
      redirect_to result[:floor]
    else
      flash[:alert] = result[:errors].full_messages.join(', ')
      render 'new', status: :unprocessable_entity
    end
  end

  def destroy
    if @slot.destroy
      flash[:notice] = 'Slot Successfully Deleted'
    else
      flash[:alert] = 'Failed to Delete Slot'
    end
    redirect_to slots_path
  end

  private

  def slot_params
    params.require(:slot).permit(:slot_number, :floor_id, :status)
  end

  def set_slot
    @slot = Slot.find(params[:id])
  rescue ActiveRecord::RecordNotFound => e
    flash[:alert] = 'Slot not found'
    redirect_to slots_path
  end
end
