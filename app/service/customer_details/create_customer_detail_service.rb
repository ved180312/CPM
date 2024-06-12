# frozen_string_literal: true

# ud services
module CustomerDetails
  class CreateCustomerDetailService
    def initialize(customer_detail, current_user)
      @customer_detail = customer_detail
      @current_user = current_user
    end

    def call
      @customer_detail.slot.status = true
      price = StripeServiceLayer.price_generator(@customer_detail)

      if @customer_detail.save && @customer_detail.slot.save && @customer_detail.name == @current_user.name
        UserDetailMailer.booking_confirmation(@customer_detail, @current_user, 'user').deliver_later
        StripeServiceLayer.slot_payment(price)
        return true
      else
        false
      end
    end
  end
end