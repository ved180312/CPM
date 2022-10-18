# frozen_string_literal: true

class UserDetailsController < ApplicationController
  before_action :check_user, only: %i[destroy edit]
  before_action :set_ud, only: %i[edit update show destroy]
  def new
    @ud = UserDetail.new
  end

  def index
    @ud = UserDetail.all
  end

  def show; end

  def edit; end

  def update
    if @ud.update(ud_params)
      UserDetailMailer.booking_confirmation(@ud, current_user).deliver_later
      flash[:notice] = 'Details Updated'
      redirect_to root_path
    else
      render 'edit', status: :unprocessable_entity
    end
  end

  def create
    CreateUserDetailService.new(params[:user_detail][:id]).call
    @ud = UserDetail.new(ud_params)
    if @ud.save && @ud.name == current_user.name
      UserDetailMailer.booking_confirmation(@ud, current_user).deliver_later
      flash[:notice] = 'Successfully applied'
      redirect_to @ud
    else
      render 'new', status: :unprocessable_entity
    end
  rescue StandardError => e
    flash[:notice] = e.message
    redirect_to floors_path
  end

  def destroy
    @ud.destroy
    redirect_to user_details_path
  end

  private

  def ud_params
    params.require(:user_detail).permit(:name, :email, :car_color, :car_number, :in_time, :out_time, :slot_id, :confirm)
  end

  def set_ud
    @ud = UserDetail.find(params[:id])
  rescue ActiveRecord::RecordNotFound => e
    redirect_to user_details_path
    flash[:notice] = e
  end

  def check_user
    return unless current_user.admin == false

    flash[:alert] = 'You cannot open this'
    redirect_to root_path
  end
end
