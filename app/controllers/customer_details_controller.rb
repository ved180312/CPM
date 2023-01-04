# frozen_string_literal: true

# customer controller
class CustomerDetailsController < ApplicationController
  before_action :check_user, only: %i[destroy edit]
  before_action :set_ud, only: %i[edit update show destroy]
  
  def new
    begin
      @ud = Slot.find(params[:id])      
      if @ud.status
        flash[:notice] = 'Already Booked'
        redirect_to floor_path
      end
    rescue => exception
      @ud = CustomerDetail.new
    end
  end

  def index
    @ud = CustomerDetail.all
  end

  def show; end

  def edit; end

  def create
    @ud = CustomerDetail.new(ud_params)
    @ud.slot.status = true
    $price = StripeServiceLayer.price_generator(@ud)
    if @ud.save && @ud.slot.save and @ud.name == current_user.name
      UserDetailMailer.booking_confirmation(@ud, current_user, 'user').deliver_later
      flash[:notice] = 'Successfully applied. Please Check Your Mail'
      StripeServiceLayer.slot_payment($price)
      redirect_to @ud
    else
      render 'new', status: :unprocessable_entity
    end
  end

  def update
    if @ud.update(ud_params)
      UserDetailMailer.booking_confirmation(@ud, @ud, 'cust').deliver_later
      flash[:notice] = 'Details Updated'
      redirect_to customer_details_path
    else
      render 'edit', status: :unprocessable_entity
    end
  end

  def destroy
    @ud.slot.status = false
    if @ud.destroy
      @ud.slot.save
      redirect_to customer_details_path
    end  
  end

  private

  def ud_params
    params.require(:customer_detail).permit(:name, :car_color, :car_number, :in_time, :out_time, :slot_id, :confirm,
                                            :user_id)
  end

  def set_ud
    @ud = CustomerDetail.find(params[:id])
  rescue ActiveRecord::RecordNotFound => e
    redirect_to customer_details_path
    flash[:notice] = e
  end

  def check_user
    return unless current_user.admin == false

    flash[:alert] = 'You cannot open this'
    redirect_to root_path
  end
end
