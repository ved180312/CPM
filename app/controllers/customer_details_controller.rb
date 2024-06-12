# frozen_string_literal: true

# customer controller  
class CustomerDetailsController < ApplicationController
  before_action :check_user, only: %i[destroy edit]
  before_action :set_ud, only: %i[edit update show destroy]

  def new
    @ud = Slot.find_by(id: params[:id])
    if @ud&.status
      flash[:notice] = 'Already Booked'
      redirect_to floor_path
    else
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
    if CustomerDetails::CreateCustomerDetailService.new(@ud, current_user).call
      flash[:notice] = 'Successfully applied. Please Check Your Mail'
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
    if CustomerDetails::DestroyCustomerDetailService.new(@ud).call
      flash[:notice] = 'Customer detail successfully deleted'
      redirect_to customer_details_path
    else
      flash[:alert] = 'Failed to delete customer detail'
      redirect_to customer_details_path
    end
  end

  def download
    @ud = CustomerDetail.find(params[:id])
    respond_to do |format|
      format.csv { send_data @ud.to_csv(current_user), filename: "#{@ud.name}-#{Date.today}.csv" }
    end
  end

  private

  def ud_params
    params.require(:customer_detail).permit(:name, :car_color, :car_number, :in_time, :out_time, :slot_id, :confirm, :user_id)
  end

  def set_ud
    @ud = CustomerDetail.find_by(id: params[:id])
    unless @ud
      flash[:alert] = 'Customer detail not found'
      redirect_to customer_details_path
    end
  end
end
